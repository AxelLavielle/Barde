//
//  SocketManager.swift
//  Barde
//
//  Created by Arnaud Perrault on 30/06/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import SwiftSocket

class SocketManager: NSObject {

    static let sharedInstance = SocketManager()

    let client = TCPClient(address: "163.172.191.206", port: 23334)

    override init() {
        super.init()
    }

    func establishConnection() {
        
        switch client.connect(timeout: 10) {
        case .success:
            let ret = readResponse(from: client)
            print(ret as Any);
            GeneratorManager.sharedInstance.listeningServer()
        case .failure(let error):
            print("ERROR", error)
        }
    }
    
    func sendRequest(data: Data, using client: TCPClient) -> Bool {
        switch client.send(data: data) {
        case .success:
            let ret = readResponse(from: client)
            
            print(ret)
            return true
        case .failure(let error):
            print("ERROR REQUEST", error)
            return false
        }
    }
    
    func readResponse(from client: TCPClient) -> [Byte]? {
        let response = client.read(1024*10)
        
        if (response != nil) {         print("response in readResponse", response) }


        return response
    }
    
    func closeConnection() {
       client.close()
    }
}
