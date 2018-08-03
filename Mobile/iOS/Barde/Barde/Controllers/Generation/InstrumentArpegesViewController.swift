//
//  InstrumentViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 11/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class InstrumentArpegesViewController: UIViewController {
    
    @IBOutlet weak var instrumentScrollView: UIScrollView!
   
    var arpegiosSelected: String! = ""
    
    var arpegiosArray: [String] = []
    
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        let instruments = InstrumentService().getAll()
        let x = 8
        var y = 0
        
        print("////")
        print(instruments)
        
        instruments?.forEach{instrument in
            y += 50
            
            let button = CheckButton(frame: CGRect(x: Int(x), y: y, width: 343, height: 30))
            button.layer.borderColor = UIColor.white.cgColor
            button.setTitle(instrument.name, for: [])
            
            self.instrumentScrollView.addSubview(button)
            
            button.topAnchor.constraint(equalTo: instrumentScrollView.topAnchor, constant: 50).isActive = true
            button.bottomAnchor.constraint(equalTo: instrumentScrollView.bottomAnchor, constant:410).isActive = true
            button.trailingAnchor.constraint(equalTo: instrumentScrollView.trailingAnchor, constant: 0).isActive = true
            button.centerXAnchor.constraint(equalTo: instrumentScrollView.centerXAnchor, constant: 0).isActive = true
            
            button.addTarget(self, action: #selector(buttonAction(_:)), for: .touchUpInside)

        }
        
    }
    
    @objc func buttonAction(_ button: CheckButton) {
        
        arpegiosSelected = button.titleLabel!.text
        
        if (arpegiosArray.contains(arpegiosSelected)) {
            arpegiosArray = arpegiosArray.filter{$0 != arpegiosSelected}

            switch (arpegiosSelected) {
            case "Trumpet":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x071, 0x0, 0x0, 0x0, 0x57, 0x0, 0x0, 0x0])
                break;
            case "Piano":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x071, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0])
                break;
            case "Saxophone":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x071, 0x0, 0x0, 0x0, 0x65, 0x0, 0x0, 0x0])
                break;
            case .none:
                break;
            case .some(_):
                break;
            }

        } else {
            arpegiosArray.append(arpegiosSelected)

            switch (arpegiosSelected) {
            case "Trumpet":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x031, 0x0, 0x0, 0x0, 0x57, 0x0, 0x0, 0x0])
                break;
            case "Piano":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x031, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0])
                break;
            case "Saxophone":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x031, 0x0, 0x0, 0x0, 0x65, 0x0, 0x0, 0x0])
                break;
            case .none:
                break;
            case .some(_):
                break;
            }
        }
        
//        if (arpegiosArray.contains(arpegiosSelected)) {
//            arpegiosArray = arpegiosArray.filter{$0 != arpegiosSelected}
//        } else {
//            arpegiosArray.append(arpegiosSelected)
//        }
//
//        UserDefaults.standard.set(arpegiosArray, forKey: "arpegiosArray")
    }
    
}
