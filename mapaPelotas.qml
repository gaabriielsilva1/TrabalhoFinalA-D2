import QtQuick
import QtLocation
import QtPositioning

Item {
    height: 300
    width: 500

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://tile.openstreetmap.org/"
        }

        PluginParameter {
            name: "osm"
            value: "mapaPel"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        zoomLevel: 13
        center: QtPositioning.coordinate(-31.7354, -52.3379)

        activeMapType: supportedMapTypes[supportedMapTypes.length - 1]
    }
}
