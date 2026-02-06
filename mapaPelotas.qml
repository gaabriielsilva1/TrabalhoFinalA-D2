import QtQuick
import QtLocation
import QtPositioning

Item {
    height: 300
    width: 500

    MapPolyline {
        id: linhaRota // <--- ESTE NOME TEM QUE SER EXATAMENTE ASSIM
        line.width: 5
        line.color: "blue"
    }

    function desenharRota(caminho) {
            console.log("Recebi a rota!");
            linhaRota.path = caminho;
        }
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
