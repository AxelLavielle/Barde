//
//  InstrumentAccordsViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 11/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class InstrumentAccordsViewController: UIViewController {
    
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
            
            let button = CheckButton(frame: CGRect(x: Int(x), y: y, width: 300, height: 30))
            button.layer.borderColor = UIColor.white.cgColor
            button.setTitle(instrument.name, for: [])

            button.layer.cornerRadius = 6
            button.layer.borderWidth = 2.0
            
            button.center.x = self.view.center.x;
            
            self.instrumentScrollView.addSubview(button)
            
            
            button.widthAnchor.constraint(equalTo: instrumentScrollView.widthAnchor, constant: 0).isActive = true
            button.trailingAnchor.constraint(equalTo: instrumentScrollView.trailingAnchor, constant: 20).isActive = true
            button.leadingAnchor.constraint(equalTo: instrumentScrollView.leadingAnchor, constant: 20).isActive = true
            
            
        }
        //button.addTarget(self, action: #selector(buttonAction), forControlEvents: .TouchUpInside)
        
    }
    
}
