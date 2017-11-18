//
//  SettingsViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/10/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit

class SettingsViewController: UIViewController, SettingMenuButtonDelegate {
    
    @IBOutlet weak var accountButton: SettingMenuButton!
    
    func buttonClicked(button: SettingMenuButton, sender: UIButton) {
        
        
        
        let storyBoard : UIStoryboard = UIStoryboard(name: "Main", bundle:nil)
        let viewController: UIViewController
        
        switch button.tag {
        case 1:
           viewController = storyBoard.instantiateViewController(withIdentifier: "AccountView")
           self.show(viewController, sender: self)
        default:
            print("lol")
        }
        
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        accountButton.delegate = self
    }

}
