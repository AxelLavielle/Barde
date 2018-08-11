//
//  AboutUsViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/08/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class AboutUsViewController: UIViewController {
    
    @IBOutlet weak var buttonBack: UIBarButtonItem!
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.title = "About us"

    }
    
    @IBAction func backButtonAction(_ sender: Any) {
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
}
