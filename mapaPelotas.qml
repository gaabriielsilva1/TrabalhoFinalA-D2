import QtQuick
import QtLocation
import QtPositioning

Item {
    id: root
    height: 300
    width: 500

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://tile.openstreetmap.org/"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        zoomLevel: 13
        center: QtPositioning.coordinate(-31.7354, -52.3379)

        activeMapType: supportedMapTypes[supportedMapTypes.length - 1]

        MapPolyline {
            id: linhaRota
            line.width: 5
            line.color: "blue"
        }
    }

    function desenharRota(caminho) {
        if (caminho && caminho.length > 0) {
            linhaRota.path = caminho;

            //zoom só funciona se o caminho tiver coordenadas reais
            if (caminho.length >= 2) {
                map.fitViewportToMapItems();
            }
        }
    }
}
