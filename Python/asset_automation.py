# Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

"""
Script highlighting specific exposed Python features.
"""

# built-in
import unreal


# ------------------------------------------------------------------------------
# Example Functions

def import_skeletal_mesh(fbx_path, game_path, asset_name):
    """
    Import a single skeletalMesh into the engine provided an FBX.

    :param str fbx_path: Path to fbx.
    :param str game_path: Game path asset location.
    :param str asset_name: Name of asset.
    :return:
    """
    # Create an import task.
    import_task = unreal.AssetImportTask()

    # Set base properties on the import task.
    import_task.filename = fbx_path
    import_task.destination_path = game_path
    import_task.destination_name = asset_name
    import_task.automated = True  # Suppress UI.

    # Set the skeletal mesh options on the import task.
    import_task.options = _get_skeletal_mesh_import_options()

    # Import the skeletalMesh.
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks(
        [import_task]  # Expects a list for multiple import tasks.
    )
    imported_assets = import_task.get_editor_property(
        "imported_object_paths"
    )

    if not imported_assets:
        unreal.log_warning("No assets were imported!")
        return

    # Return the instance of the imported SkeletalMesh
    return unreal.load_asset(imported_assets[0])


def _get_skeletal_mesh_import_options():
    """Returns hard coded SkeletalMesh import options."""
    options = unreal.FbxImportUI()
    options.import_as_skeletal = True
    options.mesh_type_to_import = unreal.FBXImportType.FBXIT_SKELETAL_MESH

    # Default to compute normals.
    import_method = unreal.FBXNormalImportMethod.FBXNIM_COMPUTE_NORMALS
    options.skeletal_mesh_import_data.normal_import_method = import_method

    # Don't import materials or textures.
    options.import_materials = False
    options.import_textures = False
    return options


def regenerate_skeletal_mesh_lods(skeletal_mesh, number_of_lods=4):
    """
    Regenerate the LODs to a specific LOD level.

    .. NOTE: EditorScriptingUtilities plugin needs to be loaded.

    :param SkeletalMesh skeletal_mesh: SkeletalMesh object.
    :param int number_of_lods: Number of LODs to generate.
    :return:
    """
    did_update_lods = skeletal_mesh.regenerate_lod(number_of_lods)
    if not did_update_lods:
        unreal.log_warning("Unable to generate LODS for {}".format(
            skeletal_mesh.get_full_name()
            )
        )


def set_metadata_tags_on_asset(asset, tags):
    """
    Sets metadata tags on a given asset.

    :param asset:
    :param tags:
    :return:
    """
    for tag in tags:
        unreal.EditorAssetLibrary.set_metadata_tag(asset, tag, tags[tag])
    unreal.EditorAssetLibrary.save_loaded_asset(asset)


def get_metadata_tags_on_asset(asset):
    """
    Grabs metadata from a given tag on an asset.

    :param object asset: Asset object that has metadata.
    :return: tag data.
    """
    return unreal.EditorAssetLibrary.get_tag_values(asset.get_full_name())


def get_selected_assets():
    """Get the assets currently selected in the Content Browser."""
    utility_base = unreal.GlobalEditorUtilityBase.get_default_object()
    return utility_base.get_selected_assets()


def save_assets(assets, force_save=False):
    """
    Saves the given asset objects.

    :param list assets: List of asset objects to save.
    :param bool force_save: Will save regardless if the asset is dirty or not.
    :return: True if all assets were saved correctly, false if not; the failed
    assets are returned if necessary.
    :rtype: bool, list[unreal.Object]
    """
    failed_assets = []
    only_if_is_dirty = not force_save
    assets = assets if isinstance(assets, list) else [assets]

    for asset in assets:
        asset_path = asset.get_full_name()
        if unreal.EditorAssetLibrary.save_asset(asset_path, only_if_is_dirty):
            unreal.log(
                "Saved newly created asset: {}".format(asset_path)
            )
        else:
            unreal.log_warning(
                "FAILED TO SAVE newly created asset: {}".format(asset_path)
            )
            failed_assets.append(asset)

    return len(failed_assets) == 0, failed_assets



