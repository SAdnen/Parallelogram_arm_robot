#ifndef _ARM_PLUGIN_HH_
#define _ARM_PLUGIN_HH_

#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <sdf/sdf.hh>
#include <gazebo/physics/Model.hh>
#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>
#include <thread>
#include <boost/function.hpp> 

namespace gazebo
{
	/// \brief A plugin to control robot joints

	class ArmPlugin : public ModelPlugin
	{
		/// \brief Constructor
		public: ArmPlugin() {}
		
		/// \brief The load function is called by Gazebo when the plugin is
		/// inserted into simulation
		/// \param[in] _model A pointer to the model that this plugin is 
		/// attached to.
		/// \param[in] _sdf A pointer to the plugin's SDF element.
		public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
		{
			// Default to zero velocity
			double velocity = 0, velocity12 = 0;
			
			//Check that the velocity element exists, then read the value
			if(_sdf->HasElement("velocity"))
				velocity = _sdf->Get<double>("velocity");
			if(_sdf->HasElement("velocity12"))
				velocity12 = _sdf->Get<double>("velocity12");
			// Store the model pointer for convenience
			this->model = _model;
			
			// Get the first joint. We are making an assumption about the model
			// having 3 joints that are the rotational joints.
			this->jointDD1 = _model->GetJoints()[6];
			this->jointDD2 = _model->GetJoints()[9];
			this->joint12 = _model->GetJoints()[1];
			//std::cerr <<"This is the joint ["<<this->model->GetName() << "]\n";
			std::cerr <<"This is the joint ["<< this->jointDD1->GetName() << "]\n";
			std::cerr <<"This is the joint ["<< this->jointDD2->GetName() << "]\n";
			std::cerr <<"This is the joint ["<< this->joint12->GetName() << "]\n";
			//Setup a P-controller, with a gain of 0.1
			this->pid = common::PID(0.1,0.0,0.0);
			// Apply the P-controller to the joint
			this->model->GetJointController()->SetVelocityPID( this->jointDD1->GetScopedName(), this->pid);
			
			// Set the joint's target velocity. This target velocity is just
			// for demonstration purposes.
			//this->model->GetJointController()->SetVelocityTarget( this->jointDD1->GetScopedName(), velocity);
			//std::cerr <<"This is the joint ["<< this->jointDD2->GetName() << "]\n";
			// Apply the P-controller to the joint
			this->model->GetJointController()->SetVelocityPID( this->jointDD2->GetScopedName(), this->pid);
			
			// Set the joint's target velocity. This target velocity is just
			// for demonstration purposes.
			//this->model->GetJointController()->SetVelocityTarget( this->jointDD2->GetScopedName(), velocity12);
			//std::cerr <<"This is the joint ["<< this->joint12->GetName() << "]\n";
			// Apply the P-controller to the joint
			this->model->GetJointController()->SetVelocityPID( this->joint12->GetScopedName(), this->pid);
			
			// Set the joint's target velocity. This target velocity is just
			// for demonstration purposes.
			//this->model->GetJointController()->SetVelocityTarget( this->joint12->GetScopedName(), velocity);
			// Create the node
			/*
			this->nodeDD1 = transport::NodePtr(new transport::Node());
			this->nodeDD1->Init(this->model->GetWorld()->GetName());
			
			/*this->nodeDD2 = transport::NodePtr(new transport::Node());
			this->nodeDD2->Init(this->model->GetWorld()->GetName());
			
			this->node12 = transport::NodePtr(new transport::Node());
			this->node12->Init(this->model->GetWorld()->GetName());*/

			// Create a topic name
			/*
			std::string topicNameDD1 = "/" + this->model->GetName() + "/arm_cmdDD1";
			
			/*std::string topicNameDD2 = "~/" + this->model->GetName() + "/arm_cmdDD2";
			
			std::string topicName12 = "~/" + this->model->GetName() + "/arm_cmd12";*/

			// Subscribe to the topic, and register a callback
			/*
			this->subDD1 = this->nodeDD1->Subscribe(topicNameDD1,
				&ArmPlugin::OnMsgDD1, this);
			/*
			this->subDD2 = this->nodeDD2->Subscribe(topicNameDD2,
				&ArmPlugin::OnMsgDD2, this);
			
			this->sub12 = this->node12->Subscribe(topicName12,
				&ArmPlugin::OnMsg12, this);*/
				
///////////////////////////ROS/////////////////////////////////////////////
	// Initialize ros, if it has not already bee initialized.
		if (!ros::isInitialized())
		{
		  int argc = 0;
		  char **argv = NULL;
		  ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
		}				
		// Create our ROS node. This acts in a similar manner to
		// the Gazebo node
		this->rosNodeDD1.reset(new ros::NodeHandle("gazebo_client"));
														
		this->rosNodeDD2.reset(new ros::NodeHandle("gazebo_clientDD2"));	
		this->rosNode12.reset(new ros::NodeHandle("gazebo_client12"));	
		
// Create a named topic, and subscribe to it.
		ros::SubscribeOptions soDD1 = ros::SubscribeOptions::create<std_msgs::Float32>(
				"/" + this->model->GetName() + "/arm_cmdDD1", 1,
				boost::bind(&ArmPlugin::OnRosMsgDD1, this, _1),
				ros::VoidPtr(), &this->rosQueueDD1);
		
		ros::SubscribeOptions soDD2 =
		  ros::SubscribeOptions::create<std_msgs::Float32>(
				"/" + this->model->GetName() + "/arm_cmdDD2",
				1,
				boost::bind(&ArmPlugin::OnRosMsgDD2, this, _1),
				ros::VoidPtr(), &this->rosQueueDD2);						
		ros::SubscribeOptions so12 =
		  ros::SubscribeOptions::create<std_msgs::Float32>(
				"/" + this->model->GetName() + "/arm_cmd12",
				1,
				boost::bind(&ArmPlugin::OnRosMsg12, this, _1),
				ros::VoidPtr(), &this->rosQueue12);
				
		this->rosSubDD1 = this->rosNodeDD1->subscribe(soDD1);				
		
		this->rosSubDD2 = this->rosNodeDD2->subscribe(soDD2);
		this->rosSub12 = this->rosNode12->subscribe(so12);
		
		// Spin up the queue helper thread.
		this->rosQueueThreadDD1 = std::thread(std::bind(&ArmPlugin::QueueThreadDD1, this));
		
		this->rosQueueThreadDD2 = std::thread(std::bind(&ArmPlugin::QueueThreadDD2, this));
		  
		this->rosQueueThread12 = std::thread(std::bind(&ArmPlugin::QueueThread12, this));
		  
		  
		      
		}
		
		
		/// \brief Set the velocity of the Velodyne
		/// \param[in] _vel New target velocity
		public: void SetVelocityDD1(const double &_vel)
		{
		  // Set the joint's target velocity.
		  this->model->GetJointController()->SetVelocityTarget(
				this->jointDD1->GetScopedName(), _vel);
		}
		
		public: void SetVelocityDD2(const double &_vel)
		{
		  // Set the joint's target velocity.
		  this->model->GetJointController()->SetVelocityTarget(
				this->jointDD2->GetScopedName(), _vel);
		}
		public: void SetVelocity12(const double &_vel)
		{
		  // Set the joint's target velocity.
		  this->model->GetJointController()->SetVelocityTarget(
				this->joint12->GetScopedName(), _vel);
		}	
					
		private: common::PID pid;
		private: physics::JointPtr jointDD1, jointDD2, joint12;
		private: physics::ModelPtr model;
		/// \brief A node used for transport
		private: transport::NodePtr nodeDD1, nodeDD2, node12;

		/// \brief A subscriber to a named topic.
		private: transport::SubscriberPtr subDD1, subDD2, sub12;
		
		///////////////////////ROS////////////////////////////////
		/// \brief A node use for ROS transport
		private: std::unique_ptr<ros::NodeHandle> rosNodeDD1, rosNodeDD2, rosNode12;

		/// \brief A ROS subscriber
		private: ros::Subscriber rosSubDD1, rosSubDD2, rosSub12;

		/// \brief A ROS callbackqueue that helps process messages
		private: ros::CallbackQueue rosQueueDD1, rosQueueDD2, rosQueue12;

		/// \brief A thread the keeps running the rosQueue
		private: std::thread rosQueueThreadDD1,  rosQueueThreadDD2, rosQueueThread12;
		
		
		/// \brief Handle incoming message
		/// \param[in] _msg Repurpose a vector3 message. This function will
		/// only use the x component.
		private: void OnMsgDD1(ConstVector3dPtr &_msg)
		{
		  this->SetVelocityDD1(_msg->x());
		}
		
		
		private: void OnMsgDD2(ConstVector3dPtr &_msg)
		{
		  this->SetVelocityDD2(_msg->x());
		}
		private: void OnMsg12(ConstVector3dPtr &_msg)
		{
		  this->SetVelocity12(_msg->x());
		}
		
		/// \brief Handle an incoming message from ROS
		/// \param[in] _msg A float value that is used to set the velocity
		/// of the Velodyne.
		public: void OnRosMsgDD1(const std_msgs::Float32ConstPtr &_msg)
		{
		  this->SetVelocityDD1(_msg->data);
		}

		/// \brief ROS helper function that processes messages
		private: void QueueThreadDD1()
		{
		  static const double timeout = 0.01;
		  while (this->rosNodeDD1->ok())
		  {
			 this->rosQueueDD1.callAvailable(ros::WallDuration(timeout));
		  }
		}
		
		public: void OnRosMsgDD2(const std_msgs::Float32ConstPtr &_msg)
		{
		  this->SetVelocityDD2(_msg->data);
		}

		/// \brief ROS helper function that processes messages
		private: void QueueThreadDD2()
		{
		  static const double timeout = 0.01;
		  while (this->rosNodeDD2->ok())
		  {
			 this->rosQueueDD2.callAvailable(ros::WallDuration(timeout));
		  }
		}
		
		public: void OnRosMsg12(const std_msgs::Float32ConstPtr &_msg)
		{
		  this->SetVelocity12(_msg->data);
		}

		/// \brief ROS helper function that processes messages
		private: void QueueThread12()
		{
		  static const double timeout = 0.01;
		  while (this->rosNode12->ok())
		  {
			 this->rosQueue12.callAvailable(ros::WallDuration(timeout));
		  }
		}								
	};
	// Tell Gazebo about this plugin, so that Gazebo cann call Load on this plugin.
	GZ_REGISTER_MODEL_PLUGIN(ArmPlugin)
}
#endif
