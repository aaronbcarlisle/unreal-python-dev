# Copyright Epic Games, Inc. All Rights Reserved.

import unreal
from . import asset_utils


def set_tag_on_asset(asset, tag_name, tag_value, save=False):
    """
    Sets the given metadata tag on the given asset.

    :param object asset: The asset to set metadata tags on.
    :param str tag_name: The name of the tag to set.
    :param str tag_value: The value of the tag to set.
    :param bool save: Save the asset or not.
    """
    unreal.EditorAssetLibrary.set_metadata_tag(asset, tag_name, tag_value)

    # save the asset if specified
    if save:
        unreal.EditorAssetLibrary.save_loaded_asset(asset)


def set_tags_on_asset(asset, tags, save=False):
    """
    Sets tags on an asset given a dictionary with tag name, tag value pairs.

    :param object asset: The asset to set metadata tags on.
    :param dict tags: A dictionary of key value pairs where key is the name of
        the tag to set the the value is the value of the tag.
    :param bool save: Whether to save the asset or not after the tags are set.
    """
    # loop through the given tags and set them on the given asset
    for tag_name, tag_value in tags.items():
        set_tag_on_asset(asset, tag_name, tag_value)

    # save the asset if specified
    if save:
        unreal.EditorAssetLibrary.save_loaded_asset(asset)


def get_asset_tags(asset):
    """
    Gets the metadata tags for the given asset.

    :param Object asset: Asset object to retrieve metadata from.
    :return: Returns the metadata tags set on the given asset.
    :rtype: dict
    """
    return unreal.EditorAssetLibrary.get_tag_values(asset.get_full_name())
