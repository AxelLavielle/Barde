//
//  Profil+CoreDataProperties.swift
//  
//
//  Created by Arnaud Perrault on 18/11/2017.
//
//

import Foundation
import CoreData


extension Profil {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<Profil> {
        return NSFetchRequest<Profil>(entityName: "Profil")
    }

    @NSManaged public var email: String?
    @NSManaged public var firstname: String?
    @NSManaged public var lastname: String?

}
