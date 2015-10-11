import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQml 2.2

Rectangle {
    width: 400
    height: 400
    
    property string key: ""
    property color iCharger_Channel1PanelColor: "lightblue"
    property color iCharger_Channel1Background: "black"
    property color iCharger_Channel2PanelColor: "#009900"
    property color iCharger_Channel2Background: "black"

    property alias ch1: channel1
    property alias ch2: channel2
    property alias volt_amps_temp: volt_amps_temp
    
    color: "black"
    
    ColumnLayout {
        anchors.fill: parent
        
        RowLayout { 
            anchors.fill: parent
            spacing: 0
            
            Channel {
                id: channel1
                panelHeaderTitleLeft.text: "01-Cycle"
                panelBorderColor: iCharger_Channel1PanelColor
                panelBackgroundColor: iCharger_Channel1Background
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: volt_amps_temp.height
                Layout.preferredWidth: parent.width / 2
            }
            
            Channel {
                id: channel2
                panelHeaderTitleLeft.text: "02-Balance"
                panelBorderColor: iCharger_Channel2PanelColor
                panelBackgroundColor: iCharger_Channel2Background
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: volt_amps_temp.height
                Layout.preferredWidth: parent.width / 2
            }
        }
        
        VoltAmpsTemp {
            id: volt_amps_temp   
            
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}

