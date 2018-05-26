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
            
        }
        //button.addTarget(self, action: #selector(buttonAction), forControlEvents: .TouchUpInside)
        
    }
    
}
