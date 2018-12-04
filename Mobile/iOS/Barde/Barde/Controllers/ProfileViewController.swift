//
//  ProfileViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 27/11/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit
import CoreData

class ProfileViewController: UIViewController, SettingMenuButtonDelegate, NSFetchedResultsControllerDelegate {
    
    @IBOutlet weak var accountButton: SettingMenuButton!
    var controller: NSFetchedResultsController <Profil>!
    @IBOutlet weak var imageSettings: UIImageView!
    
    @IBOutlet weak var tfName: UILabel!
    @IBOutlet weak var tfEmail: UILabel!
    
    func buttonClicked(button: SettingMenuButton, sender: UIButton) {
        
        switch button.tag {
        case 1:
           
            let profil: NSManagedObject
            let request = NSFetchRequest<NSFetchRequestResult>(entityName: "Profil")
            //request.predicate = NSPredicate(format: "age = %@", "12")
            request.returnsObjectsAsFaults = false
            request.fetchLimit = 1
            
            do {
                let result = try context.fetch(request)
                
                for data in result as! [NSManagedObject] {
                    
                    profil = data
                    performSegue(withIdentifier: "SettingsEditAccountView", sender: profil)
                    return
                }
            } catch {
                print("Failed")
            }
        default:
            print("lol")
        }
        
    }
    
    override func viewDidAppear(_ animated: Bool) {        
        accountButton.delegate = self
        attemptFetch()
        
        // Tap gesture for imageSettings
        let tap = UITapGestureRecognizer(target: self, action: #selector(imageSettingsAction))
        imageSettings.addGestureRecognizer(tap)
        imageSettings.isUserInteractionEnabled = true
        
        var text = UserDefaults.standard.string(forKey: "username")
        if (UserDefaults.standard.string(forKey: "firstname") != nil && UserDefaults.standard.string(forKey: "lastname") != nil) {
            let firstName = UserDefaults.standard.string(forKey: "firstname")
            let lastName = UserDefaults.standard.string(forKey: "lastname")
            text = firstName! + " " + lastName! + " (" + UserDefaults.standard.string(forKey: "username")! + ")"
        }
       
        tfName.text = text
        tfEmail.text = UserDefaults.standard.string(forKey: "email")
        
//        let request = NSFetchRequest<NSFetchRequestResult>(entityName: "Profil")
//        //request.predicate = NSPredicate(format: "age = %@", "12")
//        request.returnsObjectsAsFaults = false
//        request.fetchLimit = 1
//
//        do {
//            let result = try context.fetch(request)
//
//            for data in result as! [NSManagedObject] {
//
//                print(data)
//
//                let firstName = data.value(forKey:"firstname") as! String
//                let lastName = data.value(forKey:"lastname") as! String
//                tfName.text = firstName + " " + lastName
//                tfEmail.text = data.value(forKey:"email") as? String
//                return
//            }
//        } catch {
//            print("Failed")
//        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        configureView()
    }
    
    func configureView() {
    
        accountButton.titleLabel.text = NSLocalizedString("EditProfile.text", comment: "")
        
    }
    
    @IBAction func logoutButtonAction(_ sender: Any) {
        Alert.showLogoutAction(on: self)
    }
    
    override func viewWillAppear(_ animated: Bool) {
        attemptFetch()
    }
    
    @objc func imageSettingsAction() {
        performSegue(withIdentifier: "segueGoToSettings", sender: nil)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        
        if segue.identifier == "SettingsEditAccountView" {
            if let navController = segue.destination as? UINavigationController {
                if let chidVC = navController.topViewController as? SettingsEditAccountView{
                    chidVC.profilFromLocal = sender as? Profil
                }
            }
        }
    }
    
    func attemptFetch(){
        // function used to fetch data from coredata
        let fetchRequest: NSFetchRequest<Profil> = Profil.fetchRequest()
        
        let emailSort = NSSortDescriptor(key: "email", ascending: false)
        fetchRequest.sortDescriptors = [emailSort]
        
        let controller = NSFetchedResultsController(fetchRequest: fetchRequest, managedObjectContext: context, sectionNameKeyPath: nil, cacheName: nil)
        
        controller.delegate = self
        
        self.controller = controller
        
        do{
            try controller.performFetch()
        }catch{
            let error = error as NSError
            print("\(error)")
        }
    }
    
}
