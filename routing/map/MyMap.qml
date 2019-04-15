import QtQuick 2.5
import QtQuick.Controls 1.4
import QtLocation 5.9
import QtPositioning 5.5
import "../helper.js" as Helper

Map {
    id: map
    property alias routeQuery: routeQuery
    property alias routeModel: routeModel

    center: QtPositioning.coordinate(48.368718, -4.588330) // Plouzane
    zoomLevel: 10

    function calculateCoordinateRoute(startCoordinate, endCoordinate)
    {
        // clear away any old data in the query
        routeQuery.clearWaypoints();

        // add the start and end coords as waypoints on the route
        routeQuery.addWaypoint(startCoordinate)
        routeQuery.addWaypoint(endCoordinate)
        routeQuery.travelModes = RouteQuery.BicycleTravel
        routeQuery.routeOptimizations = RouteQuery.FastestRoute

        for (var i=0; i<9; i++) {
            routeQuery.setFeatureWeight(i, 0)
        }

        routeModel.update();

        // center the map on the start coord
        map.center = startCoordinate;
    }
    function calculateCoordinateRouteWithNodes(nodes)
    {
        // clear away any old data in the query
        routeQuery.clearWaypoints();

        // add the start and end coords as waypoints on the route
        for(var i=0; i<nodes.length; i++){
            var node = roadsData.requestLatLonFromNodes(nodes[i]);
            var coordinate = QtPositioning.coordinate(node[0],node[1])
            routeQuery.addWaypoint(coordinate)
        }
        routeQuery.travelModes = RouteQuery.BicycleTravel
        routeQuery.routeOptimizations = RouteQuery.FastestRoute

        for (var j=0; j<9; j++) {
            routeQuery.setFeatureWeight(j, 0)
        }

        routeModel.update();

        // center the map on the start coord
        map.center = QtPositioning.coordinate(roadsData.requestLatLonFromNodes(nodes[0]),roadsData.requestLatLonFromNodes(nodes[0]));
    }

    function showRouteListPage()
    {
        if (routeModel.count > 0) {
            //textToDisplay.text="Itinéraire: " + routeModel.get(0).segments[1].path
            for (var i = 0; i < routeModel.get(0).segments.length; i++) {
                textToDisplay.text+="\nInstruction: " + routeModel.get(0).segments[i].maneuver.instructionText
                        + "\nDistance: "+Helper.formatDistance(routeModel.get(0).segments[i].maneuver.distanceToNextInstruction)
                        + "\nDénivelé: "+routeModel.get(0).segments[i].path[0].altitude + "m\n"
            }
        }
    }

    RouteModel {
        id: routeModel
        plugin : map.plugin
        query:  RouteQuery {
            id: routeQuery
        }
        onStatusChanged: {
            if (status == RouteModel.Ready) {
                switch (count) {
                case 1:
                    map.showRouteListPage()
                    break
                }
            }
        }
    }

    MapItemView {
        model: routeModel
        delegate: routeDelegate
    }

    Component {
        id: routeDelegate

        MapRoute {
            route: routeData
            line.color: "#ff00ff"
            line.width: 3
            smooth: true
            opacity: 0.8
        }
    }
}
