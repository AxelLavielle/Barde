//
//  Page2ViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 01/12/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class PagePlayViewController: UIViewController {
    
    @IBOutlet weak var text: UITextView!
    
    override func viewDidLoad() {
        self.text.text = NSLocalizedString("NzH-ZM-M2a.text", comment: "")
    }
}
