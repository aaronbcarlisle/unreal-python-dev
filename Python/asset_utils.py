# Copyright Epic Games, Inc. All Rights Reserved.

# built-in
import unreal


class ImportOption(object):
    """Convenient enum class handler for normal import options."""
    COMPUTE = unreal.FBXNormalImportMethod.FBXNIM_COMPUTE_NORMALS
    IMPORT = unreal.FBXNormalImportMethod.FBXNIM_IMPORT_NORMALS
    IMPORT_WITH_TANGENTS = unreal.FBXNormalImportMethod.FBXNIM_IMPORT_NORMALS_AND_TANGENTS


class ImportType(object):
    """Convenient enum class handler for import type options."""
    ANIMATION = unreal.FBXImportType.FBXIT_ANIMATION
    SKELETAL_MESH = unreal.FBXImportType.FBXIT_SKELETAL_MESH
    STATIC_MESH = unreal.FBXImportType.FBXIT_STATIC_MESH


def create_fbx_import_task(
        fbx_path,
        game_path,
        asset_name,
        options=None,
        suppress_ui=True
):
    """
    Creates a skeletal mesh import task.

    :param str fbx_path: Path to fbx to ingest.
    :param str game_path: Game path to import the fbx in.
    :param str asset_name: The name of the SkeletalMesh to import.
    :param FbxImportUI options: Optional import options override.
    :param bool suppress_ui: Whether to suppress the import prompt or not.
    :return: Returns the SkeletalMesh import task.
    :rtype: FbxImportUI
    """
    # create an import task
    import_task = unreal.AssetImportTask()

    # set the base properties on the import task
    import_task.filename = fbx_path
    import_task.destination_path = game_path
    import_task.destination_name = asset_name
    import_task.automated = suppress_ui

    # set the SkeletalMesh base default options
    import_task.options = options or get_basic_skeletal_mesh_import_options()
    return import_task


def run_import_tasks(import_tasks):
    """
    Imports the given list of tasks.

    :param list(FbxImportUI) import_tasks: The list of tasks to import.
    :return: Returns the assets that were imported.
    :rtype: list
    """
    # import the given import tasks
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks(import_tasks)

    # discover the imported assets
    imported_assets = import_task.get_editor_property("imported_object_paths")

    # early return and log if the imported assets could not be discovered
    if not imported_assets:
        unreal.log_warning("No assets were imported, see log for details!")
        return

    # return the imported assets
    return [unreal.load_asset(asset) for asset in imported_assets]


def get_basic_import_options(
        import_type=None,
        normal_import_method=None,
        import_materials=False,
        import_textures=False
):
    """
    Sets default property values for the SkeletalMesh options and returns them.

    :param int or enum import_type: The type of import to generate options for.
        The default is SkeletalMesh.
    :param int or enum normal_import_method: The import method for normal
        computation when the mesh ingests into the Engine, default is compute.
    :param bool import_materials: Whether to import the materials or not.
    :param bool import_textures: Whether to import the textures or not.
    :return: Returns the SkeletalMesh set default options.
    :rtype: unreal.FbxImportUI
    """
    # create the options handle
    options = unreal.FbxImportUI()

    # set to import as skeletal
    options.import_as_skeletal = True
    options.mesh_type_to_import = import_type or ImportType.SKELETAL_MESH

    # determine and set the import option for normals. default to compute
    normal_import_method = normal_import_method or ImportOption.COMPUTE
    options.skeletal_mesh_import_data.normal_import_method = normal_import_method

    # don't import materials or textures
    options.import_materials = import_materials or False
    options.import_textures = import_textures or False
    return options


def regenerate_skeletal_mesh_lods(skeletal_mesh, number_of_lods=4):
    """
    Regenerate the LODs to a specific LOD level. Useful for when you've
    updated/set the LODSettings for the SkeletalMesh or for initial ingestion.

    .. NOTE: EditorScriptingUtilities plugin needs to be loaded.

    :param SkeletalMesh skeletal_mesh: The SkeletalMesh object to regenerate
        the LODs for.
    :param int number_of_lods: The number of LODs to regenerate. Default is 4.
    :return: Returns True if the LODs were regenerated, False otherwise.
    :rtype: bool
    """
    lods_regenerated = skeletal_mesh.regenerate_lod(number_of_lods)
    if not lods_regenerated:
        unreal.log_warning(
            "Unable to generate LODS for '{skeletal_mesh}'!".format(
                skeletal_mesh=str(skeletal_mesh)
            )
        )
        return False
    return True


def set_metadata_tag_on_asset(asset, tag, value, save=False):
    """
    Sets the given metadata tags on the given asset.

    :param unreal.Object asset: The asset to set metadata tags on.
    :param str tag: The name of the tag to set.
    :param str value: The value of the tag to set.
    :param bool save: Whether to save the asset or not. Default is to defer
        the save for batch operations.
    """
    unreal.EditorAssetLibrary.set_metadata_tag(asset, tag, value)

    # save the asset if specified
    if save:
        unreal.EditorAssetLibrary.save_loaded_asset(asset)


def set_metadata_tags_on_asset(asset, tags, save=False):
    """
    Convenience method for setting tags on an asset given a dictionary object.

    :param unreal.Object asset: The asset to set metadata tags on.
    :param dict tags: A dictionary of key value pairs where key is the name of
        the tag to set the the value is the value of the tag.
    :param bool save: Whether to save the asset or not after the tags are set.
    """
    # raise Exception if the given tags are not a dictionary
    if not isinstance(tags, dict):
        raise ValueError(
            "The tags argument must be of type '{tags_type}', "
            "got '{tags_type_received}'!".format(
                tags_type=str(type(dict)),
                tags_type_received=str(type(tags))
            )
        )

    # loop through the given tags and set them on the given asset
    for tag, value in tags.items():
        set_metadata_tag_on_asset(asset, tag, value)

    # save the asset if specified
    if save:
        unreal.EditorAssetLibrary.save_loaded_asset(asset)


def get_metadata_tags_on_asset(asset):
    """
    Gets the metadata tags for the given asset.

    :param unreal.Object asset: Asset object to retrieve metadata from.
    :return: Returns the metadata tags set on the given asset.
    :rtype: dict
    """
    return unreal.EditorAssetLibrary.get_tag_values(asset.get_full_name())


def get_selected_assets():
    """
    Get the selected assets in the editor content browser.

    :return: Returns the selected assets in the editor content browser.
    :rtype: list(unreal.Object)
    """
    utility_base = unreal.GlobalEditorUtilityBase.get_default_object()
    return utility_base.get_selected_assets()


def save_assets(assets, force_save=False):
    """
    Saves the given asset(s) objects.

    :param str or list(unreal.Object) assets: List of asset objects to save.
    :param bool force_save: Will save regardless if the asset is dirty or not.
    :return: Returns True if all assets were saved correctly.
    :rtype: tuple(bool, list(unreal.Object))
    """
    failed_assets = []
    if_is_dirty = not force_save  # invert default 'only_if_is_dirty' param

    # allow str or list as arguments
    assets = assets if isinstance(assets, list) else [assets]

    for asset in assets:
        asset_path = asset.get_full_name()
        asset_saved = unreal.EditorAssetLibrary.save_asset(asset_path, if_is_dirty)
        if not asset_saved:
            unreal.log_warning(
                "Failed to save the following asset: '{asset_path}'".format(
                    asset_path=asset_path
                )
            )
            failed_assets.append(asset)

    return bool(failed_assets), failed_assets



