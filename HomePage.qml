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

    property var homeWindow
    property var districtModel
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

    RowLayout {
            id: dateSelectionLayout
            spacing: 10
            anchors.top: searchRow.bottom // Correctly anchor to the previous layout
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter

            property int currentDay: parseInt(Qt.formatDate(new Date(), "d"))
            property int currentMonth: parseInt(Qt.formatDate(new Date(), "M")) - 1
            property int currentYear: parseInt(Qt.formatDate(new Date(), "yyyy"))
            property int daysInMonth: 31
            property string selectedDate: {
                // Only compute if everything is valid
                if (yearComboBox.currentIndex < 0 ||
                    monthComboBox.currentIndex < 0 ||
                    dayComboBox.currentIndex < 0 ||
                    dayComboBox.currentIndex >= dayModel.count)
                    return "";

                var year = yearComboBox.model[yearComboBox.currentIndex];
                var month = monthComboBox.currentIndex + 1;
                var day = dayModel.get(dayComboBox.currentIndex).value;

                function pad(n) { return n < 10 ? "0" + n : n }
                return year + "-" + pad(month) + "-" + pad(day);
            }

            ListModel {
                id: dayModel
            }

            ComboBox {
                id: dayComboBox
                width: 60
                model: dayModel
                textRole: "text"
                delegate: ItemDelegate { text: model.text }
            }

            ComboBox {
                id: monthComboBox
                width: 90
                model: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
                currentIndex: dateSelectionLayout.currentMonth
                onCurrentIndexChanged: dateSelectionLayout.updateDays()
            }

            ComboBox {
                id: yearComboBox
                width: 80
                model: [dateSelectionLayout.currentYear]
                currentIndex: model.indexOf(dateSelectionLayout.currentYear)
                onCurrentIndexChanged: dateSelectionLayout.updateDays()
            }

            function updateDays() {
                var year = yearComboBox.currentIndex >= 0 ? yearComboBox.model[yearComboBox.currentIndex] : dateSelectionLayout.currentYear;
                var month = monthComboBox.currentIndex >= 0 ? monthComboBox.currentIndex : dateSelectionLayout.currentMonth;
                dateSelectionLayout.daysInMonth = getDaysInMonth(year, month);
                dayModel.clear();
                for (var i = 1; i <= dateSelectionLayout.daysInMonth; ++i) {
                    dayModel.append({"text": i.toString(), "value": i});
                }
                if (dayComboBox.currentIndex >= dateSelectionLayout.daysInMonth || dayComboBox.currentIndex < 0) {
                    dayComboBox.currentIndex = dateSelectionLayout.daysInMonth - 1;
                }
            }

            function getDaysInMonth(year, month) {
                if (month === 1) { // February
                    if ((year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0)) return 29;
                    return 28;
                }
                if ([3, 5, 8, 10].indexOf(month) !== -1) return 30;
                return 31;
            }

            Component.onCompleted: {
                // Fill days immediately
                updateDays();

                // Set default indexes so they are not -1
                if (yearComboBox.currentIndex < 0)
                    yearComboBox.currentIndex = 0;

                if (monthComboBox.currentIndex < 0)
                    monthComboBox.currentIndex = currentMonth;

                if (dayComboBox.currentIndex < 0)
                    dayComboBox.currentIndex = currentDay - 1;

                console.log("Date initialized:", selectedDate);
            }
        }

        Button {
            id: searchButton
            text: "SEARCH"
            anchors.top: dateSelectionLayout.bottom // Correctly anchored to the date layout
            anchors.topMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            width: 100
            height: 40
            font.bold: true
            background: Rectangle {
                color: "purple"
                radius: 10
                opacity: searchButton.enabled ? 1.0 : 0.5
            }

            onClicked: {
                console.log(" SEARCH button clicked");

                // Check if homeWindow is set
                if (!homeWindow) {
                    console.log(" homeWindow is null or not set yet, cannot call searchRoute!");
                    return;
                }

                // Collect values
                var fromText = fromComboBox.currentText.trim();
                var toText = toComboBox.currentText.trim();
                var dateStr = dateSelectionLayout.selectedDate;

                // Validate
                if (fromText === "" || toText === "" || dateStr === "") {
                    console.log(" ERROR: One or more fields are empty. FROM:", fromText, "TO:", toText, "DATE:", dateStr);
                    return;
                }

                // Debug log values
                console.log("From:", fromText, "To:", toText, "Date:", dateStr);

                // Call C++ function
                homeWindow.searchRoute(fromText, toText, dateStr);
            }
        }


    Rectangle {
            id: resultsBox
            width: parent.width - 20
            anchors.top: searchButton.bottom
            anchors.bottom: footer.top
            anchors.topMargin: 40
            anchors.bottomMargin: 0
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

                Rectangle {
                        width: 10
                        height: parent.height
                        color: "transparent"
                    }

                Rectangle { width: 60; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Route ID"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "From"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "To"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Date"; font.bold: true; color: "white"}}
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Depart"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Arrive"; font.bold: true; color: "white" } }
                Rectangle { width: 60; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Price"; font.bold: true; color: "white" } }
                Rectangle { width: 80; height: 30; color: "#9575cd"; Text { anchors.centerIn: parent; text: "Bus No"; font.bold: true; color: "white" } }
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

                            Rectangle {
                                    width: 6
                                    height: parent.height
                                    color: "transparent"
                                }

                            Rectangle { width: 60; height: parent.height; color: "black"; Text { anchors.centerIn: parent; text: model.route_id; color: "white" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.from_district; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.to_district; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.date; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.departure_time; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.arrival_time; color: "#333" } }
                            Rectangle { width: 60; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.price; color: "#333" } }
                            Rectangle { width: 80; height: parent.height; color: "#ede7f6"; Text { anchors.centerIn: parent; text: model.bus_no; color: "#333" } }
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
                                                                    model.date,
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
    }
}
