//
//  Style+CoreDataProperties.swift
//  
//
//  Created by Arnaud Perrault on 10/04/2018.
//
//

import Foundation
import CoreData


extension Style {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<Style> {
        return NSFetchRequest<Style>(entityName: "Style")
    }

    @NSManaged public var name: String?

}
