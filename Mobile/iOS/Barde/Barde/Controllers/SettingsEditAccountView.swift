//
//  SettingsEditAccountView.swift
//  Barde
//
//  Created by Arnaud Perrault on 17/11/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData

class SettingsEditAccountView: UITableViewController {

    @IBOutlet weak var emailInput: UITextField!
    @IBOutlet weak var firstNameInput: UITextField!
    @IBOutlet weak var lastNameInput: UITextField!
    
    var profilFromLocal: Profil? // optional

    override func viewDidLoad() {
        super.viewDidLoad()
        
        loadUserData()
    }
  
    @IBAction func saveButton(_ sender: Any) {
        var profil: Profil!
        
        profil = profilFromLocal

        if let email = emailInput.text{
            profil.email = email
        }
        if let firstname = firstNameInput.text{
            profil.firstname = firstname
        }
        if let lastname = lastNameInput.text{
            profil.lastname = lastname
        }
        
        ad.saveContext()
        _ = navigationController?.popViewController(animated: true)

    }
    
    func loadUserData(){
        if let profil = profilFromLocal{
            emailInput.text = profil.email
            firstNameInput.text = profil.firstname
            lastNameInput.text = profil.lastname
        }
    }
    
    
//    func getUserData(appDelegate: AppDelegate)->AnyObject?{
//        var users: [NSManagedObject] = []
//
//        let  managedContext =
//            appDelegate.persistentContainer.viewContext
//
//        let fetchRequest =
//            NSFetchRequest<NSManagedObject>(entityName: "User")
//
//        do {
//            users = try managedContext.fetch(fetchRequest)
//
//            for user: AnyObject in users {
//                return user
//            }
//
//        } catch let error as NSError {
//            print("Could not fetch. \(error), \(error.userInfo)")
//        }
//        return nil
//    }
    
   
}

