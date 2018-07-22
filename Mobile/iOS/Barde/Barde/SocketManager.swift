//
//  SocketManager.swift
//  Barde
//
//  Created by Arnaud Perrault on 30/06/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import Starscream
import RxStarscream
import RxSwift
import SwiftSocket

class SocketManager: NSObject, WebSocketDelegate {

    static let sharedInstance = SocketManager()
    
    public var socket = WebSocket(url: URL(string: "ws://163.172.128.43:23")!)
    private let disposeBag = DisposeBag()

    let client = TCPClient(address: "163.172.128.43", port: 23)

    
    override init() {
        super.init()
    }

    
    func establishConnection() {
        switch client.connect(timeout: 10) {
        case .success:
            // Connection successful 🎉
            print("sucess connection")
            break;
        case .failure(let error):
            print("failure")
            break;
            // 💩
        }
    }
    
    func closeConnection() {
        if socket.isConnected {
            print("disconnect")
            socket.disconnect()
        } else {
            socket.connect()
        }
        
    }

    func writeText(str: String) {
        socket.write(string: str)
    }

    func websocketDidReceivePong(socket: WebSocket) {
        print("Got pong!")
    }
    
    func websocketDidConnect(socket: WebSocketClient) {
        print("websocket is connected")
    }
    
    func websocketDidDisconnect(socket: WebSocketClient, error: Error?) {
        print("websocket is disconnected: \(error)")
    }
    
    func websocketDidReceiveMessage(socket: WebSocketClient, text: String) {
        print("Received text: \(text)")
    }
    
    func websocketDidReceiveData(socket: WebSocketClient, data: Data) {
        print("Received data: \(data.count)")
    }
    
}
