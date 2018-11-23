//
//  Page1ViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 23/11/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class Page1ViewController: UIViewController {
    
    @IBAction func testAction(_ sender: Any) {
        UserDefaults.standard.set(true, forKey: "tutorial")
        
        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
      
        let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
        self.present(newViewController, animated: true, completion: nil)

    }
}
