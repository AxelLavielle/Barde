//
//  SettingsViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/10/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData

class SettingsViewController: UIViewController, SettingMenuButtonDelegate, NSFetchedResultsControllerDelegate {
    
    @IBOutlet weak var accountButton: SettingMenuButton!
    var controller: NSFetchedResultsController <Profil>!

    func buttonClicked(button: SettingMenuButton, sender: UIButton) {
    
        
        let storyBoard : UIStoryboard = UIStoryboard(name: "Main", bundle:nil)
        let viewController: UIViewController
        
        switch button.tag {
        case 1:
//           viewController = storyBoard.instantiateViewController(withIdentifier: "SettingsEditAccountView")
//           self.show(viewController, sender: self)
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
    }
    
    
    override func viewWillAppear(_ animated: Bool) {
        attemptFetch()
    }
        
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "SettingsEditAccountView" {
            if let destination = segue.destination as? SettingsEditAccountView{
                if let profil = sender as? Profil{
                    destination.profilFromLocal = profil
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
