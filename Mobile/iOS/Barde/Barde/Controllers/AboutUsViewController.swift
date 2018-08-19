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
    @IBOutlet weak var versionNumber: UILabel!

    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.title = "About us"

        configureView()
    }
    
    func configureView() {
        let nsObject: AnyObject? = Bundle.main.infoDictionary?["CFBundleShortVersionString"] as AnyObject
    
        versionNumber.text = nsObject as! String
        
    }
    
    @IBAction func facebookButtonAction(_ sender: Any) {
        UIApplication.shared.openURL(URL(string: "https://goo.gl/uebg0X")!)
    }
    
    @IBAction func twitterButtonAction(_ sender: Any) {
        UIApplication.shared.openURL(URL(string: "https://goo.gl/W13U9d")!)

    }
    
    @IBAction func soundcloudButtonAction(_ sender: Any) {
        UIApplication.shared.openURL(URL(string: "https://goo.gl/nnxWBN")!)

    }
    
    @IBAction func backButtonAction(_ sender: Any) {
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
}
