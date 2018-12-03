//
//  TutorialRootViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 01/12/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class TutorialRootViewController: UIViewController {
    
    @IBAction func skipAction(_ sender: Any) {
        UserDefaults.standard.set(true, forKey: "tutorial")
        
//        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
//
//        let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
//        self.present(newViewController, animated: true, completion: nil)
        
        if (UserDefaults.standard.bool(forKey: "fromLogin")) {
            UserDefaults.standard.set(false, forKey: "fromLogin")
            let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
    
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
            self.present(newViewController, animated: true, completion: nil)
        } else {
            dismiss(animated: true, completion: nil)
        }
        
    }
    
}
