import QtQuick 2.11
import QtQuick 2.2 as QQ2
import QtQuick.Scene3D 2.0
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import Qt3D.Logic 2.0

HLScene3D {
    property alias imageUrl: diffuseTextureImage.source

    Entity {
        id: sceneRoot

        Camera {
            id: camera
            projectionType: CameraLens.PerspectiveProjection
            fieldOfView: 45
            aspectRatio: 16/9
            nearPlane : 0.1
            farPlane : 10000.0
            position: Qt.vector3d(0.0, 0.0, 22.0)
            upVector: Qt.vector3d(0.0, 1.0, 0.0)
            viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
        }

        FirstPersonCameraController {
            camera: camera
        }

        components: [
            RenderSettings {
                activeFrameGraph: ForwardRenderer {
                    clearColor: "transparent"
                    camera: camera
                }
            },
            // Event Source will be set by the Qt3DQuickWindow
            InputSettings { }
        ]

        Entity {
            Texture2D {
                id: cubeTexture
                generateMipMaps: true
                minificationFilter: Texture.Linear
                magnificationFilter: Texture.Linear
                wrapMode {
                    x: WrapMode.Repeat
                    y: WrapMode.Repeat
                }
                TextureImage {
                    id: diffuseTextureImage
                }
            }
            components: [
                CuboidMesh {
                    xExtent: 10
                    yExtent: 10
                    zExtent: 10
                },
                TextureMaterial {
                    id: cubeMaterial
                    texture: cubeTexture
                },
                Transform {
                    id: cuboidTransform
                    property real userAngle: 0.0
                    rotation: fromAxisAndAngle(Qt.vector3d(0.5, 1, 0), userAngle)
                    translation: Qt.vector3d(0, 0, 0)
                }
            ]
        }

        QQ2.NumberAnimation {
            target: cuboidTransform
            property: "userAngle"
            duration: 5000
            from: 0
            to: 360

            loops: QQ2.Animation.Infinite
            running: true
        }
    }
}
