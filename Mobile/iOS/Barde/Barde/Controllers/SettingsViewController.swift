//
//  SettingsViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/10/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData
import Alamofire

class SettingsViewController: UIViewController, SettingMenuButtonDelegate, NSFetchedResultsControllerDelegate {
    
    @IBOutlet weak var imageRefresh: UIImageView!
    
    var userService: UserService?
    
    func buttonClicked(button: SettingMenuButton, sender: UIButton) {
        
    }
    
    @IBAction func buttonBack(_ sender: Any) {
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
    
    override func viewDidLoad() {
        // Tap gesture for imageSettings
        let tap = UITapGestureRecognizer(target: self, action: #selector(imageRefreshAction))
        imageRefresh.addGestureRecognizer(tap)
        imageRefresh.isUserInteractionEnabled = true
        
        userService = UserService()
    }
    
    
    @objc func imageRefreshAction() {
        
        let userData: NSManagedObject = (userService?.getLocalData())!
        userService?.updateUserData(data: userData)
        
    }
    
    
    
   
}
