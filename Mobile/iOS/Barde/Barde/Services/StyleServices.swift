//
//  StyleServices.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import CoreData
import Alamofire

class StyleService {
    
    var styleData = [
        "Blues",
        "Jazz"
    ]
    
    func initData() -> Bool {
        var ret = true
        
        styleData.forEach { style in
            print(style)
            ret = save(name: style)
        }
    
        return ret
    }
    
    func save(name: String) -> Bool {
        let entity = NSEntityDescription.entity(forEntityName: "Style", in: context)
        let style = NSManagedObject(entity: entity!, insertInto: context)
        
        style.setValue(name, forKey: "name")
        
        return true
    }
    
    func getAll() -> [Style]? {
        let request = NSFetchRequest<NSFetchRequestResult>(entityName: "Style")
        request.returnsObjectsAsFaults = false
        
        do {
            let results = try context.fetch(request)
            
            return results as? [Style]
        } catch {
            print("Failed")
        }
        
        return nil
    }
    
}
