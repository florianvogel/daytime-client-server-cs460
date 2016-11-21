/**
 * Author: Jayden Urch
 * Student No: 5388406
 * Email: jsu22@nau.edu
 *
 * Author: Florian Vogel
 * Student No: 5373720
 * Email: fv69@nau.edu
 *
 * Date: 11/07/2016
 */

import java.io.*;
import java.net.*;

public class JavaDaytimeClientUI extends javax.swing.JFrame {

    //Creates new form JavaDaytimeClientUI
    public JavaDaytimeClientUI() {
        initComponents();
    }

    @SuppressWarnings("unchecked")
    //GUI Setup
    // <editor-fold defaultstate="collapsed" desc="Generated Code">                          
    private void initComponents() {

        timeGroup = new javax.swing.ButtonGroup();
        yearButton = new javax.swing.JRadioButton();
        monthButton = new javax.swing.JRadioButton();
        dayButton = new javax.swing.JRadioButton();
        hourButton = new javax.swing.JRadioButton();
        minuteButton = new javax.swing.JRadioButton();
        secondButton = new javax.swing.JRadioButton();
        jLabel1 = new javax.swing.JLabel();
        startButton = new javax.swing.JButton();
        resultLabel = new javax.swing.JLabel();
        endButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setName("Daytime Client"); // NOI18N
        setResizable(false);

        timeGroup.add(yearButton);
        yearButton.setSelected(true);
        yearButton.setText("Year");

        timeGroup.add(monthButton);
        monthButton.setText("Month");

        timeGroup.add(dayButton);
        dayButton.setText("Day");

        timeGroup.add(hourButton);
        hourButton.setText("Hour");

        timeGroup.add(minuteButton);
        minuteButton.setText("Minute");

        timeGroup.add(secondButton);
        secondButton.setText("Second");

        jLabel1.setText("Which time information do you want to recieve?");

        startButton.setText("Start");
        startButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                startButtonActionPerformed(evt);
            }
        });

        endButton.setText("End");
        endButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                endButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(resultLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 293, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addGap(22, 22, 22)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel1)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(yearButton)
                                    .addComponent(monthButton)
                                    .addComponent(dayButton))
                                .addGap(66, 66, 66)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(secondButton)
                                    .addComponent(minuteButton)
                                    .addComponent(hourButton)))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(startButton)
                                .addGap(18, 18, 18)
                                .addComponent(endButton)))))
                .addContainerGap(40, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(21, 21, 21)
                .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 19, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(yearButton)
                    .addComponent(hourButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(monthButton)
                    .addComponent(minuteButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(dayButton)
                    .addComponent(secondButton))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(startButton)
                    .addComponent(endButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 25, Short.MAX_VALUE)
                .addComponent(resultLabel)
                .addGap(42, 42, 42))
        );

        pack();
    }// </editor-fold>                        

    public static final String SERVER_IP = "127.0.0.1";
    public static final int SERVER_PORT = 23657;
    
    //Y = year; M = month; D = day; h = hour; m = minute; s = second
    public String radioSelect(){
        if(yearButton.isSelected()){return "Y";}
        if(monthButton.isSelected()){return "M";}
        if(dayButton.isSelected()){return "D";}
        if(hourButton.isSelected()){return "h";}
        if(minuteButton.isSelected()){return "m";}
        else return "s";
    }
        
    private void startButtonActionPerformed(java.awt.event.ActionEvent evt) {                                            
        
	
        try{
            Socket s = new Socket(SERVER_IP, SERVER_PORT);	//open Socket
            PrintStream toServer = new PrintStream(s.getOutputStream());				//open Stream
            BufferedReader fromServer = new BufferedReader(new InputStreamReader(s.getInputStream()));
            String X;
            toServer.println("" + radioSelect());							//send input to server
            X=fromServer.readLine();
//                System.out.println("From Server:\n"+X);                                 //output response from server
            if(X!=null){
                resultLabel.setText("Result: " + X);
            }else{
                resultLabel.setText("Error: No input from Server!");
            }
        s.close();									//close socket
//        return;
        }catch(Exception e){resultLabel.setText("Connection Closed");}
    }                                           

    private void endButtonActionPerformed(java.awt.event.ActionEvent evt) {                                          
        System.exit(0);
    }                                         

    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(JavaDaytimeClientUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(JavaDaytimeClientUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(JavaDaytimeClientUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(JavaDaytimeClientUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new JavaDaytimeClientUI().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify                     
    private javax.swing.JRadioButton dayButton;
    private javax.swing.JButton endButton;
    private javax.swing.JRadioButton hourButton;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JRadioButton minuteButton;
    private javax.swing.JRadioButton monthButton;
    private javax.swing.JLabel resultLabel;
    private javax.swing.JRadioButton secondButton;
    private javax.swing.JButton startButton;
    private javax.swing.ButtonGroup timeGroup;
    private javax.swing.JRadioButton yearButton;
    // End of variables declaration                   
}
