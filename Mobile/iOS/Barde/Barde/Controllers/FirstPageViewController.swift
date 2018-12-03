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
    let network = NetworkManager.sharedInstance

    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        network.reachability.whenUnreachable = { reachability in
            self.showOfflinePage()
        }
    
    }
    
    private func showOfflinePage() -> Void {
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: "NetworkUnavailable", sender: self)
        }
    }

    override func viewDidAppear(_ animated: Bool) {    
        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)

        let tokenExist = UserDefaults.exists(key: "Token")
        
        if tokenExist == true {
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
            self.present(newViewController, animated: true, completion: nil)        }
     
    }
    
    func openTutorial() {
        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)

        if (!UserDefaults.standard.bool(forKey: "tutorial")) {
            self.performSegue(withIdentifier: "Tutorial", sender: self)
        } else {
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
            self.present(newViewController, animated: true, completion: nil)
        }
    }
    
}
