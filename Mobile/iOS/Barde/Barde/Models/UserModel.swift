//
//  UserModel.swift
//  Barde
//
//  Created by Arnaud Perrault on 23/10/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData

class UserModel {
    var firstName: String = ""
    var lastName: String = ""
    var email: String = ""
    
    func getUserData(appDelegate: AppDelegate)->AnyObject?{
        var users: [NSManagedObject] = []
        
        let  managedContext =
            appDelegate.persistentContainer.viewContext
        
        let fetchRequest =
            NSFetchRequest<NSManagedObject>(entityName: "User")
        
        do {
            users = try managedContext.fetch(fetchRequest)
            
            for user: AnyObject in users {
                return user
            }
            
        } catch let error as NSError {
            print("Could not fetch. \(error), \(error.userInfo)")
        }
        return nil
    }
    
    func saveUserData(userData: UserModel, appDelegate: AppDelegate) {
        
        print("ooo", userData.email);
        
        let managedContext = appDelegate.persistentContainer.viewContext
    
        let entity = NSEntityDescription.entity(forEntityName: "User",
                                                in: managedContext)!
    
        let user = NSManagedObject(entity: entity,
                                       insertInto: managedContext)
    
        user.setValue(userData.firstName, forKeyPath: "firstname")
        user.setValue(userData.lastName, forKeyPath: "lastname")
        user.setValue(userData.email, forKeyPath: "email")
    

        do {
            try managedContext.save()
        } catch let error as NSError {
            print("Could not save. \(error), \(error.userInfo)")
        }
    }

}


//
//extension User
//{
//    // MARK: Contact info
//    var firstName: String
//    var lastName: String
//    var email: String
//}
//
//func getUserData()->UserModel? {
//
//    var users: [UserModel] = []
//
//    guard let appDelegate =
//        UIApplication.shared.delegate as? AppDelegate else {
//            return nil
//    }
//
//    let managedContext =
//        appDelegate.persistentContainer.viewContext
//
//    //2
//    let fetchRequest =
//        NSFetchRequest<NSManagedObject>(entityName: "User")
//
//    //3
//    do {
//        users = try managedContext.fetch(fetchRequest)
//
//        for user: UserModel in users {
//            return user
//        }
//
//    } catch let error as NSError {
//        print("Could not fetch. \(error), \(error.userInfo)")
//    }
//
//}

