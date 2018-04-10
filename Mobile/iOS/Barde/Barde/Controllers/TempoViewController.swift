//
//  TempoViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 09/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class TempoViewController: UIViewController {
    
    @IBOutlet weak var currentTempoLabel: UILabel!
    @IBOutlet weak var tempoSlider: UISlider!
    
    @IBAction func tempoSliderAction(_ sender: Any) {
        let currentValue = Int(tempoSlider.value)
        currentTempoLabel.text =  "\(currentValue) BPM"
    }
    
    
    override func viewDidLoad() {
        currentTempoLabel.text =  "60 BPM"
    }
    
}
