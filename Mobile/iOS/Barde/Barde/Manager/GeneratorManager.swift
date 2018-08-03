//
//  GeneratorManager.swift
//  Barde
//
//  Created by Arnaud Perrault on 27/07/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation

class GeneratorManager: NSObject {
    
    static let sharedInstance = GeneratorManager()

    override init() {
        super.init()
    }
    
    func sendData(arr: [UInt8]) {
       SocketManager.sharedInstance.sendRequest(data: Data(bytes: arr), using: SocketManager.sharedInstance.client)
    }
    
    func writeDataToFile(arr: [UInt8]) {
        
        let pointer = UnsafeBufferPointer(start: arr, count: arr.count)
        let data = Data(buffer:pointer)
        let paths = FileManager.default

        let filename = paths.urls(for: .documentDirectory, in: .userDomainMask).last?.appendingPathComponent("test.mid")
        print(">>A", filename)

        
        if !paths.fileExists(atPath: (filename?.path)!) {
            print("create")
            paths.createFile(atPath: (filename?.path)!, contents: data, attributes: nil)
        }
        
        do {
            let fileHandle = try FileHandle(forWritingTo: filename!)
            fileHandle.seekToEndOfFile()
            fileHandle.write(data)
            fileHandle.closeFile()
        } catch {
            print("Error writing to file \(error)")
        }
    
       
    }
    
    func getDocumentsDirectory() -> URL {
        let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
        return paths[0]
    }
    
    func listeningServer() {
        DispatchQueue.global(qos: .background).async {
            while (true) {
                let res = SocketManager.sharedInstance.readResponse(from: SocketManager.sharedInstance.client)
                
                if (res != nil) {
                    print("RES:", res)
                    switch (res![0])
                    {
                    case 4:
                        let mid = res![4..<res!.count]
                        print("MIDI", Array<UInt8>(mid))
                        self.writeDataToFile(arr: Array<UInt8>(mid))
                        break;
                    default:
                        print("NA");
                        break;
                    }
                }
            }
        }
    }
}
