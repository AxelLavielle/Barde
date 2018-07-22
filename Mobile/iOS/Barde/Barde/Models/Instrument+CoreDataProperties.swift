//
//  Instrument+CoreDataProperties.swift
//  
//
//  Created by Arnaud Perrault on 10/04/2018.
//
//

import Foundation
import CoreData


extension Instrument {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<Instrument> {
        return NSFetchRequest<Instrument>(entityName: "Instrument")
    }

    @NSManaged public var name: String?

}
