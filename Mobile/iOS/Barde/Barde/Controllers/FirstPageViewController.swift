//
//  FirstPageViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 19/12/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import Foundation

class FirstPageViewController: UIViewController {
    
    override func viewDidAppear(_ animated: Bool) {
//        let storyboard = UIStoryboard(name: "Main", bundle: nil)
//        let ivc = storyboard.instantiateViewController(withIdentifier: "FirstPageViewController")
//        ivc.modalTransitionStyle = .crossDissolve
//        self.present(ivc, animated: true)
        
        
        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
        
        let tokenExist = UserDefaults.exists(key: "Token")
        
        print("token: \(tokenExist)")
        
        if tokenExist == true {
            
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
            self.present(newViewController, animated: true, completion: nil)
            
        }
    }
    
}
