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
        switch client.connect(timeout: 10) {
        case .success:
            let ret = readResponse(from: client)
            print(ret as Any);
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
       
//        let fileManager = FileManager.default
//
//        guard let documentsDirectory = fileManager.urls(for: .documentDirectory, in: .userDomainMask).last else {
//            fatalError("No document directory found in application bundle.")
//        }
////
////        let midFile = documentsDirectory.appendingPathComponent("file.mid")
////
////        if fileManager.fileExists(atPath: midFile.path) {
////            do {
////                print("remove midFile")
////                try fileManager.removeItem(atPath: midFile.path)
////            } catch {
////                print("error removing file")
////            }
////        }
//        
//        
//        GeneratorManager.sharedInstance.writeDataToFile(arr: [])
//    
//       let soundFont = documentsDirectory.appendingPathComponent("SoundFont.sf2")
//        
//        if fileManager.fileExists(atPath: soundFont.path) {
//            do {
//                print("remove SoundFont.sf2")
//                try fileManager.removeItem(atPath: soundFont.path)
//            } catch {
//                print("error removing file")
//            }
//        }
//        
       client.close()
    }
}
