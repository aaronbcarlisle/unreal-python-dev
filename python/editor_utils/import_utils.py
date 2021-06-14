# Copyright Epic Games, Inc. All Rights Reserved.

import unreal
from asset_utils import asset_tools


class ImportOptions(object):
    """Convenient enum class handler for normal import options."""
    COMPUTE = unreal.FBXNormalImportMethod.FBXNIM_COMPUTE_NORMALS
    IMPORT = unreal.FBXNormalImportMethod.FBXNIM_IMPORT_NORMALS
    IMPORT_WITH_TANGENTS = (
        unreal.FBXNormalImportMethod.FBXNIM_IMPORT_NORMALS_AND_TANGENTS
    )


class ImportTypes(object):
    """Convenient enum class handler for import type options."""
    ANIMATION = unreal.FBXImportType.FBXIT_ANIMATION
    SKELETAL_MESH = unreal.FBXImportType.FBXIT_SKELETAL_MESH
    STATIC_MESH = unreal.FBXImportType.FBXIT_STATIC_MESH


def create_fbx_import_task(
        fbx_path,
        game_path,
        asset_name,
        import_options,
        suppress_ui=True
):
    """
    Creates a import task for the given fbx.

    :param str fbx_path: Path to import.
    :param str game_path: Path to import to.
    :param str asset_name: Name of the asset.
    :param FbxImportUI import_options: The import options for the import task.
    :param bool suppress_ui: Suppress the ui or not.
    :return: Returns the import task.
    :rtype: AssetImportTask.
    """
    # create an import task
    import_task = unreal.AssetImportTask()

    # set the base properties on the import task
    import_task.filename = fbx_path
    import_task.destination_path = game_path
    import_task.destination_name = asset_name
    import_task.automated = suppress_ui

    # set the import options on the import task
    import_task.options = import_options
    return import_task


def run_import_tasks(import_tasks):
    """
    Imports the given list of tasks.

    :param list(FbxImportUI) import_tasks: The list of tasks to import.
    :return: Returns the assets that were imported.
    :rtype: list
    """
    # import the given import tasks
    asset_tools.import_asset_tasks(import_tasks)

    # return the imported assets as paths
    return import_task.get_editor_property("imported_object_paths")


def get_basic_skeletal_import_options(
        import_method=None,
        import_materials=False,
        import_textures=False
):
    """
    Get some basic default import options for a SkeletalMesh import.

    :param int or enum import_method: The normals import method.
    :param bool import_materials: Whether to import the materials or not.
    :param bool import_textures: Whether to import the textures or not.
    :return: Returns the import options.
    :rtype: unreal.FbxImportUI
    """
    # create the options handle
    options = unreal.FbxImportUI()

    # set to import as skeletal
    options.import_as_skeletal = True
    options.mesh_type_to_import = ImportTypes.SKELETAL_MESH

    # determine and set the import option for normals
    import_method = import_method or ImportOptions.COMPUTE
    options.skeletal_mesh_import_data.import_method = import_method

    # determine and set whether to import materials and textures
    options.import_materials = import_materials or False
    options.import_textures = import_textures or False
    return options

