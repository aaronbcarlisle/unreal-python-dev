# Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

"""
One-off script for GDC sizzle reel
"""

# Built-in
import random

# Third-party
import unreal


# ------------------------------------------------------------------------------
# Controls - These can be edited

ACTOR_COUNT_DIMENSIONS = (
    5,  # count in X direction
    5,  # count in Y direction
    5,  # count in Z direction
)

# Separation between actors
ACTOR_SEPARATION_DISTANCE = 200

# The static mesh to spawn
MESH_TO_SPAWN = '/Engine/BasicShapes/Cube'

# Sequence time in seconds
SEQUENCE_LENGTH = 5

# ------------------------------------------------------------------------------
# Constants/Controls

CHANNELS_TO_KEY = [
    'Location.X',
    'Location.Y',
    'Location.Z',
]


# ------------------------------------------------------------------------------
# Helper functions

def add_actor_to_sequence(target_sequence, actor):
    """
    Add the specified cube into the target sequence with keys

    :param unreal.MovieSceneSequence target_sequence: The sequence to add to
    :param unreal.Actor actor: The cube to be added
    :return:
    """
    frame_rate = target_sequence.get_display_rate()
    frame_rate = frame_rate.numerator / frame_rate.denominator

    actor_location = actor.get_actor_location()
    actor_location = [actor_location.x, actor_location.y, actor_location.z]

    sequence = target_sequence.add_possessable(actor)
    transform_track = sequence.add_track(
        unreal.MovieScene3DTransformTrack
    )

    new_section = transform_track.add_section()
    new_section.set_range_seconds(0, SEQUENCE_LENGTH)
    channels = new_section.get_channels()

    # Add some motion flare
    adjusted_location = [v + random.randint(-500, 500) for v in actor_location]

    for channel in channels:
        if channel.get_name() not in CHANNELS_TO_KEY:
            continue

        # Key the ranges as needed
        channel_index = CHANNELS_TO_KEY.index(channel.get_name())
        channel.add_key(
            unreal.FrameNumber(0),
            actor_location[channel_index],
            interpolation=unreal.MovieSceneKeyInterpolation.LINEAR
        )
        channel.add_key(
            unreal.FrameNumber(SEQUENCE_LENGTH * frame_rate),
            adjusted_location[channel_index],
            interpolation=unreal.MovieSceneKeyInterpolation.LINEAR
        )


def create_new_level_sequence(new_level_sequence_path, new_level_sequence_name):
    """
    Create a new level sequence in engine

    :param str new_level_sequence_path: the new level sequence target directory
    :param str new_level_sequence_name: name of the new level to be created

    :return: The new level sequence if it was created, or None if it failed
    :rtype: unreal.LevelSequence | NoneType
    """
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    return asset_tools.create_asset(
        asset_name=new_level_sequence_name,
        package_path=new_level_sequence_path,
        asset_class=unreal.LevelSequence,
        factory=unreal.LevelSequenceFactoryNew()
    )


def spawn_actor(location):
    """
    Spawn a cube at a defined location

    :param unreal.Vector location: The location to place the cube
    """
    new_cube = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor,
        location=location,
    )
    mesh = unreal.load_object(None, MESH_TO_SPAWN)

    mesh_component = new_cube.get_editor_property('static_mesh_component')
    mesh_component.set_static_mesh(mesh)

    return new_cube


# ------------------------------------------------------------------------------
# Main functionality

def main():
    """Execute the main functionality of the example script"""
    locations = []
    for x in range(ACTOR_COUNT_DIMENSIONS[0]):
        for y in range(ACTOR_COUNT_DIMENSIONS[1]):
            for z in range(ACTOR_COUNT_DIMENSIONS[2]):
                locations.append(
                    (
                        x * ACTOR_SEPARATION_DISTANCE,
                        y * ACTOR_SEPARATION_DISTANCE,
                        z * ACTOR_SEPARATION_DISTANCE
                    )
                )

    total_frames = len(locations)
    text_label = 'Generating Example Sequence'

    new_sequence = create_new_level_sequence('/Game', 'ExamplePythonSequence')
    with unreal.ScopedSlowTask(total_frames, text_label) as example_task:
        example_task.make_dialog(True)
        for cube_location in locations:
            if example_task.should_cancel():
                break

            cube = spawn_actor(unreal.Vector(*cube_location))

            # Add the cube to the generated sequence
            add_actor_to_sequence(new_sequence, cube)

            # Move the progress bar
            example_task.enter_progress_frame()

    # Automatically open the sequence
    unreal.AssetToolsHelpers.get_asset_tools().open_editor_for_assets(
        [new_sequence]
    )


if __name__ == '__main__':
    main()
