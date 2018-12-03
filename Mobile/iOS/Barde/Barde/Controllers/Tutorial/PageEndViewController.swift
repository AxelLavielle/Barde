//
//  PageEndViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 02/12/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class PageEndViewController: UIViewController {
    
    @IBAction func goAction(_ sender: Any) {
        UserDefaults.standard.set(true, forKey: "tutorial")
        dismiss(animated: true, completion: nil)
    }
    
}
