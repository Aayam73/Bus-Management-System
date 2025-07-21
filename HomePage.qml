import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15


Rectangle {
    width: Screen.width
    height: Screen.height
    color: "#e0c3fc"
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#8ec5fc" }
        GradientStop { position: 1.0; color: "#e0c3fc" }
    }

    property StackView stackView: StackView.view

    ListModel {
            id: routeListModel
    }

    Connections {
            target: homeWindow
            function onSearchResultsReady(routesFromCpp) {
                console.log("Received routes count:", routesFromCpp.length)
                routeListModel.clear()
                for (var i = 0; i < routesFromCpp.length; ++i) {
                    routeListModel.append(routesFromCpp[i])
                }
                console.log("routeListModel count:", routeListModel.count)
                if (routeListModel.count > 0) {
                    console.log("First item in routeListModel:", JSON.stringify(routeListModel.get(0)))
                } else {
                    console.log("routeListModel is empty after update.")
                }

                Qt.callLater(function() { // Call later to allow layout to settle
                    console.log("DEBUG: resultsBox (w,h):", resultsBox.width, resultsBox.height);
                    // Ensure headerRow is defined before trying to access its height
                    // Added a check, though with the structural fix, it should be fine.
                    if (typeof headerRow !== 'undefined') {
                        console.log("DEBUG: headerRow (h):", headerRow.height);
                    } else {
                        console.log("DEBUG: headerRow is still undefined here!");
                    }
                    console.log("DEBUG: resultsScrollView (w,h):", resultsScrollView.width, resultsScrollView.height);
                    console.log("DEBUG: resultsList (w,h):", resultsList.width, resultsList.height);
                    console.log("DEBUG: footer (h):", footer.height);
                });
            }
        }



    Image {
        id: logo
        source: "qrc:/images/images/logo.png"
        width: 100
        height: 50
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        fillMode: Image.PreserveAspectFit
    }

    Text {
        text: "Hamro Bus Sewa"
        font.bold: true
        font.pixelSize: 22
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        color: "#333"
    }

    Button {
        text: "Account"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 12
        background: Rectangle {
            color: "#ff88aa"
            radius: 10
        }
    }

    RowLayout {
        id: searchRow
        anchors.top: parent.top
        anchors.topMargin: 80
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20

        Label {
            text: "FROM"
            color: "#ffffff"
            font.bold: true
        }

        ComboBox {
            id: fromComboBox
                width: 150
                model: districtModel
                textRole: "display"
                editable: true
                currentIndex: -1

                contentItem: Item {
                    width: parent.width
                    height: parent.height

                    TextInput {
                        id: comboInputFrom
                        anchors.fill: parent
                        text: fromComboBox.editText
                        font: fromComboBox.font
                        color: fromComboBox.editText === "" && !comboInputFrom.activeFocus ? "transparent" : "#ffffff"
                        onTextChanged: fromComboBox.editText = text
                    }

                    Text {
                        anchors.verticalCenter: comboInputFrom.verticalCenter
                        anchors.left: comboInputFrom.left
                        anchors.leftMargin: 4
                        color: "#999"
                        visible: comboInputFrom.text === "" && !comboInputFrom.activeFocus
                        text: "From"
                        font: fromComboBox.font
                        // Avoid interfering with input events
                        MouseArea {
                            anchors.fill: parent
                            enabled: false
                        }
                    }
                }
            }

        Label {
            text: "TO"
            color: "#ffffff"
            font.bold: true
        }

        ComboBox {
                id: toComboBox
                width: 150
                model: districtModel
                textRole: "display"
                editable: true
                currentIndex: -1

                contentItem: Item {
                    width: parent.width
                    height: parent.height

                    TextInput {
                        id: comboInputTo
                        anchors.fill: parent
                        text: toComboBox.editText
                        font: toComboBox.font
                        color: toComboBox.editText === "" && !comboInputTo.activeFocus ? "transparent" : "#ffffff"
                        onTextChanged: toComboBox.editText = text
                    }

                    Text {
                        anchors.verticalCenter: comboInputTo.verticalCenter
                        anchors.left: comboInputTo.left
                        anchors.leftMargin: 4
                        color: "#999"
                        visible: comboInputTo.text === "" && !comboInputTo.activeFocus
                        text: "To"
                        font: toComboBox.font
                        MouseArea {
                            anchors.fill: parent
                            enabled: false
                        }
                    }
                }
            }
    }

    Button {
        id: searchButton
        text: "SEARCH"
        anchors.top: searchRow.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        width: 100
        height: 40
        font.bold: true
        background: Rectangle {
            color: "purple"
            radius: 10
        }
        onClicked: {
                       console.log("Search button clicked")
                       console.log("From:", fromComboBox.currentText)
                       console.log("To:", toComboBox.currentText)

                       if (fromComboBox.currentText === "" || toComboBox.currentText === "") {
                           console.log("Please enter both FROM and TO fields.")
                           return
                       }

                       homeWindow.searchRoute(fromComboBox.currentText, toComboBox.currentText)
                   }

    }


    Rectangle {
            id: resultsBox
            width: parent.width - 20
            anchors.top: searchButton.bottom
            anchors.bottom: footer.top
            anchors.topMargin: 20
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#d1c4e9"
            radius: 10
            border.color: "red"
            border.width: 2
            clip: true

            // 🔹 Header Row - Moved out of the Column to ensure ID is always accessible
            Row {
                id: headerRow // IMPORTANT: ID is now here
                spacing: 10
                width: parent.width - (resultsColumn.padding * 2) // Reference resultsColumn's padding

                Rectangle { width: 60; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Route ID"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "From"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "To"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Depart"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Arrive"; font.bold: true; color: "white" } }
                Rectangle { width: 60; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Price"; font.bold: true; color: "white" } }
                Rectangle { width: 60; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Bus No"; font.bold: true; color: "white" } }
                Rectangle { width: 100; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Driver"; font.bold: true; color: "white" } }
                Rectangle { width: 100; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Cell No"; font.bold: true; color: "white" } }
                Rectangle { width: 40; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Seats"; font.bold: true; color: "white" } }
                Rectangle { width: 60; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Book"; font.bold: true; color: "white" } }
            }

            Column {
                id: resultsColumn // Give the Column an ID
                anchors.top: headerRow.bottom // Anchor below headerRow
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom // Fill the rest of resultsBox
                spacing: 5
                padding: 5

                // 🔹 Dynamic List from C++ (inside ScrollView again)
                ScrollView {
                    id: resultsScrollView
                    width: parent.width // Parent is resultsColumn
                    height: parent.height // Take all available height in resultsColumn
                    clip: true
                    background: Rectangle { color: "lightblue"; opacity: 0.5 } // DEBUG: ScrollView background

                    ListView {
                        id: resultsList
                        model: routeListModel
                        width: parent.width
                        height: contentHeight // Crucial for ListView inside ScrollView to determine its natural size
                        clip: true
                        spacing: 5

                        delegate: Row {
                            width: resultsList.width // Delegate width should match ListView width
                            height: 40 // Each row is 40px high
                            spacing: 10

                            Rectangle { width: 60; height: parent.height; color: "black"; Text { anchors.centerIn: parent; text: model.route_id; color: "white" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.from_district; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.to_district; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.departure_time; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.arrival_time; color: "#333" } }
                            Rectangle { width: 60; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.price; color: "#333" } }
                            Rectangle { width: 60; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.bus_no; color: "#333" } }
                            Rectangle { width: 100; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.driver_info; color: "#333" } }
                            Rectangle { width: 100; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.drivers_cellno; color: "#333" } }
                            Rectangle { width: 40; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.seats; color: "#333" } }

                            Rectangle {
                                width: 60; height: parent.height; radius: 5; color: "#7e57c2"
                                MouseArea {
                                    anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        homeWindow.openBookingPage(
                                                                    model.route_id,
                                                                    model.from_district,
                                                                    model.to_district,
                                                                    model.departure_time,
                                                                    model.arrival_time,
                                                                    model.price,
                                                                    model.bus_no,
                                                                    model.driver_info,
                                                                    model.drivers_cellno,
                                                                    model.seats
                                                                )
                                    }
                                    onEntered: parent.color = "#9575cd"; onExited: parent.color = "#7e57c2"
                                }
                                Text { anchors.centerIn: parent; color: "white"; font.bold: true; text: "Book" }
                            }
                        }
                    }
                }
            }
        }


    Rectangle {
        id: footer
        width: parent.width
        height: 40
        anchors.bottom: parent.bottom
        color: "#d1c4e9"
        opacity: 0.9

        Text {
            text: "Welcome to the Bus Management System. Here you can search bus schedules, book seats, and view account details."
            anchors.centerIn: parent
            font.pixelSize: 12
            color: "#333"
        }
    }
}
