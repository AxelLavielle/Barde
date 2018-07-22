//
//  Profil+CoreDataProperties.swift
//  Barde
//
//  Created by Arnaud Perrault on 22/02/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//
//

import Foundation
import CoreData

extension Profil {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<Profil> {
        return NSFetchRequest<Profil>(entityName: "Profil")
    }

    @NSManaged public var birthdate: String?
    @NSManaged public var email: String?
    @NSManaged public var firstname: String?
    @NSManaged public var lastname: String?
    @NSManaged public var username: String?
}
