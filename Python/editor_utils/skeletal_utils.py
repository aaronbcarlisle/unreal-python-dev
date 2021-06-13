# Copyright Epic Games, Inc. All Rights Reserved.

# built-in
import unreal

skeletal_mesh_library = unreal.EditorSkeletalMeshLibrary()


def get_sockets(skeletal_mesh):
    """
    Gets the sockets attached to the given SkeletalMesh.

    :param SkeletalMesh skeletal_mesh: Asset to get socket from.
    :param SkeletalMesh skeletal_mesh: Asset to get the skeleton from.
    :return: Returns the sockets for the given SkeletalMesh.
    :rtype: list or dict
    """
    socket_count = skeletal_mesh.num_sockets()
    if not socket_count:
        return []

    # get the sockets by index and return the socket objects
    return [skeletal_mesh.get_socket_by_index(s) for s in range(socket_count)]


def get_socket_transform(socket):
    """
    Convenience method for getting a sockets transform.

    :param Socket socket: The socket to get the transform for.
    :return: Returns the sockets transform as an unreal Transform object.
    :rtype: Transform
    """
    return unreal.Transform(
        socket.relative_location,
        socket.relative_rotation,
        socket.relative_scale
    )


def create_socket(skeletal_mesh, parent_bone_name, transform, socket_name):
    """
    Creates a socket on the given SkeletalMesh.

    :param SkeletalMesh skeletal_mesh: SkeletalMesh to creates socket on.
    :param str parent_bone_name: Name of the bone to create the socket on.
    :param Transform transform: The transform object to position the socket.
    :param str socket_name: The name of the socket.
    :return: Returns the created socket.
    :rtype: SkeletalMeshSocket
    """
    skeleton = get_skeleton(skeletal_mesh)

    # FIXME: Currently not exposed in UE5 but is exposed for StaticMesh.
    # I believe in C++ you add a socket to a SkeletalMesh via FEditableSkeleton
    # which is also not exposed.
    skeleton.create_socket(parent_bone_name, transform, socket_name)
    return skeleton.find_socket(socket_name)


def copy_socket_to_target(socket, skeletal_mesh):
    """
    Copies the given socket to the given SkeletalMesh.

    :param SkeletalMeshSocket socket: Socket object to copy.
    :param SkeletalMesh skeletal_mesh: SkeletalMesh to copy the socket to.
    :return: Returns the copied socket object.
    :rtype: SkeletalMeshSocket
    """

    # grab the socket name and parent bone
    socket_name = socket.socket_name
    bone_name = socket.bone_name

    # early return if the socket already exists
    if skeletal_mesh.find_socket(socket_name):
        return

    # determine the sockets transform location
    transform = get_socket_transform(socket)

    # create the socket on the target skeleton
    return create_socket(skeletal_mesh, bone_name, transform, socket_name)


def copy_sockets_to_target(source_skeletal_mesh, target_skeletal_mesh):
    """
    Copies the sockets from one SkeletalMesh to another.

    :param SkeletalMesh source_skeletal_mesh: Copy from SkeletalMesh.
    :param SkeletalMesh target_skeletal_mesh: Copy to SkeletalMesh.
    :return: Returns the sockets copied on to the target SkeletalMesh.
    :rtype: list(SkeletalMeshSocket)
    """

    # early return if no sockets are found on the source asset
    if not source_skeletal_mesh.num_sockets():
        asset_name = source_skeletal_mesh.get_full_name()
        unreal.log_warning(
            "No sockets could be found for '{asset_name}'!".format(
                asset_name=asset_name
            )
        )
        return

    # get the sockets from the source SkeletalMesh
    source_sockets = get_sockets(source_skeletal_mesh)

    # copy the sockets to the target skeleton
    [copy_socket_to_target(s, target_skeletal_mesh) for s in source_sockets]

    # return the new sockets on the target SkeletalMesh
    return get_sockets(target_skeletal_mesh)


def get_skeleton(skeletal_mesh):
    """
    Gets the skeleton from the given SkeletalMesh.

    :param SkeletalMesh skeletal_mesh: SkeletalMesh to get skeleton from.
    :return: Returns the skeleton associated with the given SkeletalMesh.
    :rtype: Skeleton
    """
    # NOTE: Some releases don't have the skeleton property exposed on the asset
    # it can only be grabbed by using the get_editor_property method, which
    # works in all releases.
    return skeletal_mesh.get_editor_property("skeleton")


def regenerate_lods(skeletal_mesh, number_of_lods=4):
    """
    Regenerates the LODs for the given SkeletalMesh.

    :param SkeletalMesh skeletal_mesh: The asset to regenerate the LODs for.
    :param int number_of_lods: The number of LODs to regenerate. Default is 4.
    :return: Returns True if the LODs were regenerated, otherwise False.
    :rtype: bool
    """
    return skeletal_mesh.regenerate_lod(number_of_lods)


def get_vertex_count(skeletal_mesh, lod_level=0):
    """
    Queries a skeletal mesh for the number of vertices present

    :param SkeletalMesh skeletal_mesh: SkeletalMesh to get the vertex count.
    :param int lod_level: The LOD to query.
    :return: Returns the vertex count for the given SkeletalMesh.
    :rtype: int
    """
    # get the vertex count
    vertex_count = skeletal_mesh_library.get_num_verts(
        skeletal_mesh,
        lod_level
    )
    # return 0 if the vertex count is None
    return vertex_count or 0
