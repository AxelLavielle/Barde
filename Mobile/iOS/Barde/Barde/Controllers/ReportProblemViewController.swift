//
//  SettingsEditAccountView.swift
//  Barde
//
//  Created by Arnaud Perrault on 17/11/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData

class ReportProblemViewController: UIViewController, UITextViewDelegate {
    
    @IBOutlet weak var tvDescription: UITextView!
    @IBOutlet weak var buttonBack: UIBarButtonItem!
    var userService: UserService?

    override func viewDidLoad() {
        super.viewDidLoad()
        tvDescription.delegate = self
        
        userService = UserService()

        self.navigationItem.title = "Comment"
        tvDescription.text = "Write your message..."
        tvDescription.textColor = .lightGray
    }
    
    @IBAction func backButtonAction(_ sender: Any) {
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
    
    func textViewDidBeginEditing(_ textView: UITextView) {
        if (tvDescription.text == "Write your message...")
        {
            tvDescription.text = ""
            tvDescription.textColor = .black
        }
        
        self.navigationItem.setHidesBackButton(true, animated: false)
        
        navigationItem.rightBarButtonItem = UIBarButtonItem(title: "Send", style: .plain, target: self, action: #selector(validChange(_:)))
        navigationItem.leftBarButtonItem = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissChange(_:)))
    }
    
    func textViewDidEndEditing(_ textView: UITextView)
    {
        if (tvDescription.text == "")
        {
            tvDescription.text = "Write your message..."
            tvDescription.textColor = .lightGray
        }
        tvDescription.resignFirstResponder()
    }

    
    @objc func validChange(_ sender: Any) {
        self.navigationItem.setHidesBackButton(false, animated: true)
        self.navigationItem.rightBarButtonItem = nil;
        self.navigationItem.leftBarButtonItem = buttonBack;
        
        tvDescription.resignFirstResponder()
        self.view.endEditing(true)
        
        if let description = tvDescription.text{
            if (!description.isEmpty)
            {
                userService?.reportProblem(data: description)
                let refreshAlert = UIAlertController(title: "Message sent.", message: "Your message has been sent.", preferredStyle: UIAlertControllerStyle.alert)
                
                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                }))
                
                present(refreshAlert, animated: true, completion: nil)

            } else {
                let refreshAlert = UIAlertController(title: "Empty message.", message: "Field \"Message\" can't be empty.", preferredStyle: UIAlertControllerStyle.alert)
                
                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                }))
                
                present(refreshAlert, animated: true, completion: nil)
            }
        }
      

    
    }
    
    @objc func dismissChange(_ sender: Any) {
        self.navigationItem.setHidesBackButton(false, animated: true)
        self.navigationItem.rightBarButtonItem = nil;
        self.navigationItem.leftBarButtonItem = buttonBack;
        tvDescription.resignFirstResponder()
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
}

