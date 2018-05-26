//
//  InstrumentServices.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import CoreData

class InstrumentService {
    
    var instrumentData = [
        "Piano",
        "Trumpet",
        "Saxophone"
    ]
    
    func initData() -> Bool {
        var ret = true
        
        instrumentData.forEach { instrument in
            print(instrument)
            ret = save(name: instrument)
        }
        
        return ret
    }
    
    func save(name: String) -> Bool {
        let entity = NSEntityDescription.entity(forEntityName: "Instrument", in: context)
        let style = NSManagedObject(entity: entity!, insertInto: context)
        
        style.setValue(name, forKey: "name")
        
        return true
    }
    
    func getAll() -> [Instrument]? {
        let request = NSFetchRequest<NSFetchRequestResult>(entityName: "Instrument")
        request.returnsObjectsAsFaults = false
        
        do {
            let results = try context.fetch(request)
            
            return results as? [Instrument]
        } catch {
            print("Failed")
        }
        
        return nil
    }
    
}
