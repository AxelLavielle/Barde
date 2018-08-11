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
        
        
        UserDefaults.standard.set(currentValue, forKey: "tempoValue")
        
        let stringValue = String(format: "%02X", currentValue)
        let hexValue = Array(stringValue.utf8)
        print(currentValue, stringValue, hexValue, [0x1, 0x0, 0x0, 0x0, 0x51, 0x0, 0x0, 0x0, hexValue[1], 0x0, 0x0, 0x0]);
        GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x51, 0x0, 0x0, 0x0, hexValue[1], 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
    }
    
    
    override func viewDidLoad() {
        currentTempoLabel.text =  "70 BPM"
    }
    
}
