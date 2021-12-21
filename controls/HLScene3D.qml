import QtQuick.Scene3D 2.0
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import Qt3D.Logic 2.0

Scene3D {
    id: scene3d
    anchors.fill: parent
    anchors.leftMargin: 10
    anchors.topMargin: 10
    anchors.rightMargin: 10
    anchors.bottomMargin: 10
    focus: true
    aspects: ["input", "logic"]
    cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
}
