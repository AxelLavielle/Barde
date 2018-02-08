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
            let indexPath = NSIndexPath(row: 0, section: 0)
            let profil = controller.object(at: indexPath as IndexPath)
            performSegue(withIdentifier: "SettingsEditAccountView", sender: profil)
        default:
            print("lol")
        }
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        accountButton.delegate = self
        attemptFetch()
        
        // Tap gesture for imageSettings
        let tap = UITapGestureRecognizer(target: self, action: #selector(imageSettingsAction))
        imageSettings.addGestureRecognizer(tap)
        imageSettings.isUserInteractionEnabled = true
        
        
        let request = NSFetchRequest<NSFetchRequestResult>(entityName: "Profil")
        //request.predicate = NSPredicate(format: "age = %@", "12")
        request.returnsObjectsAsFaults = false
        request.fetchLimit = 1
        
        do {
            let result = try context.fetch(request)
            
            for data in result as! [NSManagedObject] {
                
                print(data)
                
                let firstName = data.value(forKey:"firstname") as! String
                let lastName = data.value(forKey:"lastname") as! String
                tfName.text = firstName + " " + lastName
                tfEmail.text = data.value(forKey:"email") as? String
                return
            }
        } catch {
            print("Failed")
        }
    }
    
    @IBAction func logoutButtonAction(_ sender: Any) {
        
        let alertController = UIAlertController(title: "Déconnexion", message: "Voulez-vous vous déconnecter ?", preferredStyle: .actionSheet)
        
        alertController.addAction(UIAlertAction(title: "Se déconnecter", style: .destructive, handler: { (action) -> Void in
            print("Delete button tapped")
            Utils().deleteAllRecord(entity: "Profil")
            UserDefaults.standard.removeObject(forKey: "Token")
            
            let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "FirstPageViewController") as! FirstPageViewController
            self.present(newViewController, animated: true, completion: nil)
        }))
        
        alertController.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: { (action) -> Void in
            print("Cancel button tapped")
        }))
        
        self.present(alertController, animated: true, completion: nil)
        
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        attemptFetch()
    }
    
    @objc func imageSettingsAction()
    {
        performSegue(withIdentifier: "segueGoToSettings", sender: nil)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "SettingsEditAccountView" {
            if let navController = segue.destination as? UINavigationController {
                if let chidVC = navController.topViewController as? SettingsEditAccountView{
                    if let profil = sender as? Profil{
                        chidVC.profilFromLocal = profil
                    }
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
