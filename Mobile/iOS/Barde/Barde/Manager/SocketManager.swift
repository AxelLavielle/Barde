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

    let client = TCPClient(address: "163.172.191.206", port: 8080)

    override init() {
        super.init()
    }

    func establishConnection() {
        switch client.connect(timeout: 1000) {
        case .success:
            readResponse(from: client)
            GeneratorManager.sharedInstance.listeningServer()
            print("SUCCESS SOCKET")
        case .failure(let error):
            print("ERROR", error)
        }
    }
    
    func sendRequest(data: Data, using client: TCPClient) -> Bool {
        switch client.send(data: data) {
        case .success:
            return true
        case .failure(let error):
            print("ERROR REQUEST", error)
            return false
        }
    }
    
    func readResponse(from client: TCPClient) -> [Byte]? {
        
        let response = client.read(1024*10)
        

        return response
    }
    
    func closeConnection() {
        
        let paths = FileManager.default
        
        let filename = paths.urls(for: .documentDirectory, in: .userDomainMask).last?.appendingPathComponent("test.mid")
        
        if paths.fileExists(atPath: (filename?.path)!) {
            print("create")
            
            do {
                try paths.removeItem(atPath: (filename?.path)!)
            } catch {
                print("error removing file")
            }
        }
        
       client.close()
    }
}
