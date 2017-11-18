//
//  SettingsAccountView.swift
//  Barde
//
//  Created by Arnaud Perrault on 26/10/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData

class SettingsAccountView: UIViewController, NSFetchedResultsControllerDelegate {
    
    @IBOutlet weak var lastNameLabel: UILabel!
    @IBOutlet weak var firstNameLabel: UILabel!
    @IBOutlet weak var emailLabel: UILabel!
    
    var controller: NSFetchedResultsController <Profil>!
   
    override func viewDidLoad() {
        super.viewDidLoad()
    
        attemptFetch()
        populate()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        attemptFetch()
        populate()
    }
    
    @IBAction func editButton(_ sender: Any) {
        let indexPath = NSIndexPath(row: 0, section: 0)
        let profil = controller.object(at: indexPath as IndexPath)
        performSegue(withIdentifier: "SettingsEditAccountView", sender: profil)
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
    
    func populate() {
        let indexPath = NSIndexPath(row: 0, section: 0)
        let profil = controller.object(at: indexPath as IndexPath)
        
        lastNameLabel.text = (profil.value(forKey: "lastname") ?? "") as? String
        firstNameLabel.text = (profil.value(forKey: "firstname") ?? "") as? String
        emailLabel.text = (profil.value(forKey: "email") ?? "") as? String
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
