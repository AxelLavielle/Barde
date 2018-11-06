//
//  FileManager.swift
//  Barde
//
//  Created by Arnaud Perrault on 07/08/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation

class CustomFileManager: NSObject {
    
    static let sharedInstance = CustomFileManager()
    
    let midiFile: String = "file.mid"
    let soundBank: String = "SoundFont.sf2"
    let fileManager = FileManager.default
    
    func deleteFile(file: URL) {
        do {
            try fileManager.removeItem(atPath: (file.path))
            print("remove to:", file.path)

        } catch let error as NSError {
            print("Error: \(error.domain)")
        }
    }
    
    func createFile(file: URL) {
        do {
            if (!fileExist(file: file.path)) {
                let data = Data(bytes: [0x0])
                fileManager.createFile(atPath: (file.path), contents: data, attributes: nil)
                print("create to:", file.path)
            }
            
            try "".write(to: file, atomically: true, encoding: .utf8)
            print("remove content")
        } catch let error {
            print(error)
        }

    }
    
    func fileExist(file: String) -> Bool {
        let directory = getDirectory()
        // Get URL for dest file (in Documents directory)
        let writableFileURL = directory.appendingPathComponent(file)
        
        // If dest file doesn’t exist yet
        if (try? writableFileURL.checkResourceIsReachable()) == nil {
            return false
        }
        
        return true
    }
    
    func writeToFile(file: String, arr: [UInt8]) {
        let pointer = UnsafeBufferPointer(start: arr, count: arr.count)
        let data = Data(buffer:pointer)
        let url = getFileUrl(file: file)
        
        let isExist = fileExist(file: file)
        
        if (!isExist)
        {
            fileManager.createFile(atPath: (url.path), contents: data, attributes: nil)
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
    }
    
    func getDirectory() -> URL {
        guard let documentsDirectory = fileManager.urls(for: .documentDirectory, in: .userDomainMask).last else {
            fatalError("No document directory found in application bundle.")
        }
        
        return documentsDirectory
    }
    
    func getFileUrl(file: String) -> URL {
        return getDirectory().appendingPathComponent(file)
    }
    
    func makeWritableCopy(named destFileName: String, ofResourceFile originalFileName: String) throws -> URL {
        
        let directory = getDirectory()
        // Get URL for dest file (in Documents directory)
        let writableFileURL = directory.appendingPathComponent(destFileName)
        
        // If dest file doesn’t exist yet
        if (try? writableFileURL.checkResourceIsReachable()) == nil {
            // Get original (unwritable) file’s URL
            guard let originalFileURL = Bundle.main.url(forResource: originalFileName, withExtension: nil) else {
                fatalError("Cannot find original file “\(originalFileName)” in application bundle’s resources.")
            }
            
            // Get original file’s contents
            let originalContents = try Data(contentsOf: originalFileURL)
            
            // Write original file’s contents to dest file
            try originalContents.write(to: writableFileURL, options: .atomic)
            print("Made a writable copy of file “\(originalFileName)” in “\(directory)\\\(destFileName)”.")
            
        } else { // Dest file already exists
            // Print dest file contents
            // let contents = try String(contentsOf: writableFileURL, encoding: String.Encoding.utf8)
            //print("File “\(destFileName)” already exists in “\(documentsDirectory)”.\nContents:\n\(contents)")
        }
        
        // Return dest file URL
        return writableFileURL
    }
    
}
