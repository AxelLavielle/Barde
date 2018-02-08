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
    func buttonClicked(button: SettingMenuButton, sender: UIButton) {
        
    }
    
    @IBAction func buttonBack(_ sender: Any) {
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
}
