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
            print("request ok", res)
        }
    }

    func listeningServer() {
        DispatchQueue.global(qos: .background).async {
            while (true) {
                let res = SocketManager.sharedInstance.readResponse(from: SocketManager.sharedInstance.client)
                
                if (res != nil) {
                    print("RES in listening:", res as Any)
                        print("RES0>", res![0])
                    switch (res![0])
                    {
                    case 4:
                        let mid2 = res![4..<res!.count]
        
                        print("MIDI in list", Array<UInt8>(mid2))
                        //CustomFileManager.sharedInstance.writeToFile(file: "file.mid", arr: Array<UInt8>(mid2))
                        
                        let arr = Array<UInt8>(mid2)
                        let file = "file.mid"
                        
                        let pointer = UnsafeBufferPointer(start: arr, count: arr.count)
                        let data = Data(buffer:pointer)
                        let url = CustomFileManager.sharedInstance.getFileUrl(file: file)
                        
                        let isExist = CustomFileManager.sharedInstance.fileExist(file: file)
                        
                        if (!isExist)
                        {
                            FileManager.default.createFile(atPath: (url.path), contents: data, attributes: nil)
                            print("create to:", url.path)
                        } else {
                            do {
                                try "".write(to: url, atomically: false, encoding: .utf8)
                            } catch {
                                print(error)
                            }
                        }
                        
                        do {
                            let fileHandle: FileHandle? = try FileHandle(forWritingTo: url)
                            
                            if fileHandle == nil {
                                print("File open failed")
                                
                                
                            } else {
                                print("write to:", url.path)
                                fileHandle?.seekToEndOfFile()
                                
                                print("Data in write function :", Array<UInt8>(data))
                                let array = data.withUnsafeBytes {
                                    [UInt8](UnsafeBufferPointer(start: $0, count: data.count - 2))
                                }
                                let data2 = Data(array)
                                
                                print("Data2 in write function :", Array<UInt8>(data2))
                                
                                
                                fileHandle?.write(data2)
                                fileHandle?.closeFile()
                            }
                        } catch {
                            print("Error writing to file \(error)")
                        }
                        
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
