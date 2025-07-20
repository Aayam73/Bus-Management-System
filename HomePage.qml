import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    width: Screen.width
    height: Screen.height
    color: "#e0c3fc"
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#8ec5fc" }
        GradientStop { position: 1.0; color: "#e0c3fc" }
    }

    property StackView stackView: StackView.view

    Image {
        id: logo
        source: "qrc:/images/images/logo.png"
        width: 50
        height: 50
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        fillMode: Image.PreserveAspectFit
    }

    Text {
        text: "BUS MANAGEMENT SYSTEM"
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

        TextField {
                id: fromField
                width: 280
                placeholderText: "From"

                onTextChanged: {
                    filteredFrom = districtList.filter(d => d.toLowerCase().indexOf(fromField.text.toLowerCase()) !== -1)
                    fromSuggestions.visible = filteredFrom.length > 0 && fromField.text.length > 0
                }
            }

            ListView {
                id: fromSuggestions
                width: fromField.width
                height: Math.min(150, contentHeight)
                visible: false
                model: filteredFrom
                clip: true

                delegate: Item {
                    width: parent.width
                    height: 30

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            fromField.text = modelData
                            fromSuggestions.visible = false
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData
                        }
                    }
                }
            }

        Label {
            text: "TO"
            color: "#ffffff"
            font.bold: true
        }

        TextField {
            id: toField
            width: 120
            placeholderText: "Destination"
            background: Rectangle { color: "#dfe9f3"; radius: 5 }
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
                       console.log("Search clicked:", fromField.text, toField.text)
                       if (fromField.text === "" || toField.text === "") {
                           console.log("Please enter both FROM and TO fields.")
                           return
                       }
                       homeWindow.searchRoute(fromField.text, toField.text)
                   }
    }

    Rectangle {
        id: resultsBox
        width: parent.width - 20
        height: 300
        anchors.top: searchButton.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#d1c4e9"
        radius: 10
        border.color: "#444"
        border.width: 1

        Column {
            anchors.fill: parent
            spacing: 5
            padding: 5

            // 🔹 Header Row
            RowLayout {
                width: parent.width
                spacing: 10

                Text { text: "Route ID"; width: 60; font.bold: true }
                Text { text: "From"; width: 80; font.bold: true }
                Text { text: "To"; width: 80; font.bold: true }
                Text { text: "Depart"; width: 80; font.bold: true }
                Text { text: "Arrive"; width: 80; font.bold: true }
                Text { text: "Price"; width: 60; font.bold: true }
                Text { text: "Bus No"; width: 60; font.bold: true }
                Text { text: "Driver"; width: 100; font.bold: true }
                Text { text: "Cell No"; width: 100; font.bold: true }
                Text { text: "Seats"; width: 40; font.bold: true }
            }

            // 🔹 ListView
            ListView {
                id: resultsList
                model: homeWindow.model
                clip: true
                height: parent.height - 60  // Subtract header height

                delegate: Rectangle {
                    height: 40
                    width: resultsBox.width
                    color: index % 2 === 0 ? "#f3e5f5" : "#e1bee7"

                    RowLayout {
                        anchors.fill: parent
                        spacing: 10
                        anchors.margins: 5

                        Text { text: route_id; width: 60 }
                        Text { text: from_district; width: 80 }
                        Text { text: to_district; width: 80 }
                        Text { text: departure_time; width: 80 }
                        Text { text: arrival_time; width: 80 }
                        Text { text: price; width: 60 }
                        Text { text: bus_no; width: 60 }
                        Text { text: driver_info; width: 100 }
                        Text { text: drivers_cellno; width: 100 }
                        Text { text: seats; width: 40 }
                    }
                    Button {
                        text: "Book"
                        onClicked: {
                            stackView.push({item: "qrc:/BookingPage.qml", properties: { routeId: model.route_id }})

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
