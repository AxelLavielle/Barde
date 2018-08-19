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
       let res = SocketManager.sharedInstance.sendRequest(data: Data(bytes: arr), using: SocketManager.sharedInstance.client)
        
        if res {
            print("request ok")
        }
    }
//
//    func writeDataToFile(arr: [UInt8]) {
//
//        let pointer = UnsafeBufferPointer(start: arr, count: arr.count)
//        let data = Data(buffer:pointer)
//        let paths = FileManager.default
//
//        let filename = getDocumentsDirectory().appendingPathComponent("file.midi")
////        print(">>A", filename)
////
////
//        if !paths.fileExists(atPath: (filename.path)) {
//            print("create")
//            paths.createFile(atPath: (filename.path), contents: data, attributes: nil)
//        }
//
//        do {
//            let fileHandle = try FileHandle(forWritingTo: filename)
//            let currentData = try Data(contentsOf: filename)
////            print(currentData)
////            var mid2 = currentData[0..<currentData.count-2]
////
////            try paths.removeItem(atPath: (filename.path))
////                paths.createFile(atPath: (filename.path), contents: data, attributes: nil)
////
////            print("write", fileHandle, mid2)
////            fileHandle.write(mid2)
//            fileHandle.seekToEndOfFile()
//            fileHandle.write(data)
//            fileHandle.closeFile()
//        } catch {
//            print("Error writing to file \(error)")
//        }
//
//
//    }
//
    func listeningServer() {
        DispatchQueue.global(qos: .background).async {
            while (true) {
                let res = SocketManager.sharedInstance.readResponse(from: SocketManager.sharedInstance.client)
                
                if (res != nil) {
                    print("RES:", res as Any, "RES0>", res![0])
                    switch (res![0])
                    {
                    case 4:
                        let mid2 = res![4..<res!.count]
                        
                        print("MIDI", Array<UInt8>(mid2))
                        CustomFileManager.sharedInstance.writeToFile(file: "file.mid", arr: Array<UInt8>(mid2))
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
