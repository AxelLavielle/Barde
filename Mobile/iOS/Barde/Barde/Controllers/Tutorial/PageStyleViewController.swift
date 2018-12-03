//
//  PageStyleViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 03/12/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class PageStyleViewController: UIViewController {

    @IBOutlet weak var text: UITextView!
    override func viewDidLoad() {
        self.text.text = NSLocalizedString("izt-oB-kfJ.text", comment: "<#T##String#>")
    }
}
