//
//  OfflinePageViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 13/08/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class OfflinePageViewController: UIViewController {
    let network = NetworkManager.sharedInstance
    
    @IBAction func buttonAction(_ sender: Any) {
        NetworkManager.isReachable { _ in
            self.showMainController()
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        network.reachability.whenReachable = { reachability in
            self.showMainController()
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        navigationController?.setNavigationBarHidden(true, animated: animated)
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        navigationController?.setNavigationBarHidden(false, animated: animated)
    }
    
    private func showMainController() -> Void {
        self.performSegue(withIdentifier: "MainController", sender: self)
    }
}
