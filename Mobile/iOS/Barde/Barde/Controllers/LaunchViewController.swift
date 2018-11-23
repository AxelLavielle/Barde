//
//  ViewController.swift
//  reachability-playground
//
//  Created by Neo Ighodaro on 25/10/2017.
//  Copyright © 2017 CreativityKills Co. All rights reserved.
//

import UIKit

class LaunchViewController: UIViewController {
    
    let network: NetworkManager = NetworkManager.sharedInstance
    @IBOutlet weak var versionNumberLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        NetworkManager.isUnreachable { _ in
            self.showOfflinePage()
        }
        
        NetworkManager.isReachable { _ in
            self.showMainPage()
        }
        
        configureView()
    }
    
    func configureView() {
        let nsObject: AnyObject? = Bundle.main.infoDictionary?["CFBundleShortVersionString"] as AnyObject
        
        versionNumberLabel.text = nsObject as? String
        
        if (!UserDefaults.standard.bool(forKey: "tutorial")) {
            self.performSegue(withIdentifier: "Tutorial", sender: self)
        }
    }
    
    private func showOfflinePage() -> Void {
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: "NetworkUnavailable", sender: self)
        }
    }
    
    private func showMainPage() -> Void {
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: "MainController", sender: self)
        }
    }
}

