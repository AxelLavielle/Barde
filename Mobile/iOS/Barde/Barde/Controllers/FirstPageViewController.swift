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
    
    @IBOutlet weak var buttonRegister: RoundButton!
    @IBOutlet weak var buttonLogin: RoundButton!
    
    override func viewDidAppear(_ animated: Bool) {
//        let storyboard = UIStoryboard(name: "Main", bundle: nil)
//        let ivc = storyboard.instantiateViewController(withIdentifier: "FirstPageViewController")
//        ivc.modalTransitionStyle = .crossDissolve
//        self.present(ivc, animated: true)
        
        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
        
        let tokenExist = UserDefaults.exists(key: "Token")
        
        if tokenExist == true {
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
            self.present(newViewController, animated: true, completion: nil)
            buttonLogin.isEnabled = true
            buttonRegister.isEnabled = true
        }
        
        NetworkManager.sharedInstance.reachability?.whenUnreachable = { reachability in
            
            self.showOfflinePage()
            
            let refreshAlert = UIAlertController(title: "No internet connection", message: "Make sure you device is connected to the internet", preferredStyle: UIAlertControllerStyle.alert)
            
            refreshAlert.addAction(UIAlertAction(title: "Ok", style: .default, handler: { (action: UIAlertAction!) in
            }))
            
            let alertWindow = UIWindow(frame: UIScreen.main.bounds)
            alertWindow.rootViewController = UIViewController()
            alertWindow.windowLevel = UIWindowLevelAlert + 1;
            alertWindow.makeKeyAndVisible()
            
            alertWindow.rootViewController?.present(refreshAlert, animated: true, completion: nil)
        }
    }
    
    private func showOfflinePage() -> Void {
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: "NetworkUnavailable", sender: self)
        }
    }
}
